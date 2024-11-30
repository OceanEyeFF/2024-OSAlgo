// 参考自 https://www.cnblogs.com/qicosmos/archive/2013/04/28/3048919.html
// 发现一个效果和我差不多，但是代码比我写的好的，所以改了一下。
// 我的实现是不用类型擦除，C++11就可以编译，而且使用更简单。
// 网址中的实现需要自行实现类型擦除或者使用C++17，boost库，不过代码更简单。
// 因为类型擦除的实现方式更简洁，所以消息总线更新为这样。
// 注意通知操作不要太耗时，因为目前只有同步通知的Notify。未来会加入AsyncNotify

/*
  传统观察者模式中 Observer 是基类，这带来了非常强的耦合，强度仅次于友元。
  这种耦合不仅限制了成员函数的名字、参数、返回值，还限制了成员函数所属的类型（必须是
  Observer 的派生类）。 Observer 是基类，这意味着如果 Foo
  想要观察两个类型的事件（比如时钟和温度），需要使用多继承。
  如果要重复观察同一类型的事件（比如 1 秒钟一次的心跳和 30 秒钟一次的自检），
  就要用到一些方式来 work around，因为不能从一个 Base class 继承两次。
  https://blog.csdn.net/solstice/article/details/5238671
*/

#pragma once
#include <any>
#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>

namespace detail {

// 模板递归获取不定参数类型名
template <typename... Args>
struct TypeName;

template <typename FirstArg, typename... OtherArgs>
struct TypeName<FirstArg, OtherArgs...> {
  static std::string name() {
    return std::string(typeid(FirstArg).name()) + " " +
           TypeName<OtherArgs...>::name();
  }
};

template <>
struct TypeName<> {
  static std::string name() { return ""; }
};

}  // namespace detail

class MessageBus {
 public:
  // 非成员函数, 需要手动传入参数类型，最好能修改成自动推导参数类型
  template <typename... Args, typename F,
            typename = typename std::enable_if<
                !std::is_member_function_pointer<F>::value>::type>
  static void Attach(std::string const &topic, F &&func) {
    std::function<void(Args...)> ff = [&](Args... args) {
      func(std::forward<Args>(args)...);
      return;
    };
    func_map_.insert(std::make_pair(GetKey<Args...>(topic), std::move(ff)));
  }

  // 非const类成员函数指针
  template <typename R, typename ClassType, typename ThisPtr, typename... Args>
  static void Attach(std::string const &topic, R (ClassType::*func)(Args...),
                     ThisPtr this_ptr) {
    std::function<void(Args...)> ff = [&, this_ptr, func](Args... args) {
      (this_ptr->*func)(args...);
      return;
    };
    func_map_.insert(std::make_pair(GetKey<Args...>(topic), std::move(ff)));
  }

  // const类成员函数指针
  template <typename R, typename ClassType, typename ThisPtr, typename... Args>
  static void Attach(std::string const &topic,
                     R (ClassType::*func)(Args...) const, ThisPtr this_ptr) {
    std::function<void(Args...)> ff = [&, this_ptr, func](Args... args) {
      (this_ptr->*func)(args...);
      return;
    };
    func_map_.insert(std::make_pair(GetKey<Args...>(topic), std::move(ff)));
  }

  template <typename... Args>
  static void Detach(std::string const &topic) {
    std::string args_GetTypeName = GetTypeName<Args...>();
    auto range = func_map_.equal_range(topic + args_GetTypeName);
    func_map_.erase(range.first, range.second);
  }

  template <typename... Args>
  static void Notify(std::string const &topic, Args... args) {
    std::string key = GetKey<Args...>(topic);
    auto range = func_map_.equal_range(key);

    for (auto iter = range.first; iter != range.second; ++iter) {
      std::function<void(Args...)> func =
          std::any_cast<std::function<void(Args...)>>(iter->second);
      func(args...);
    }
  }

 private:
  template <typename... Args>
  static std::string GetKey(std::string const &topic) {
    return topic + " : " + GetTypeName<Args...>();
  }

  template <typename... Args>
  static std::string GetTypeName() {
    return ::detail::TypeName<Args...>::name();
  }

 private:
  static inline std::unordered_multimap<std::string, std::any> func_map_;
};
