<!---
   Copyright (C) 2024  All rights reserved.

   Author        : OceanEyeFF
   Email         : fdch00@163.com
   File Name     : CodeReview.md
   Last Modified : 2024-09-10 01:28
   Describe      : 

--->

CodeReview
=====

### 前言
个人的建议是
学习 https://www.piglei.com/articles/three-little-things-on-code-review/
然后继续阅读本文

### CodeReview的目的

1. 学习好的代码实现(对于阅读代码的和编写代码的都是一样)
2. 修正表意不明的影响阅读的代码
3. 学习语言的艺术

### CodeReview的格式

#### 代码内Review
在源代码需要修改的地方进行注释
1. 使用注释格式，区别于代码内保留注释格式 *#define COMMENT()* 请使用 *//* 或 _'/* */'_
2. 充分说明修改意见和理由
3. 友好交流，不能影响原代码结构
4. 在代码末尾注明评审人和时间

#### 代码外Review
使用Markdown文件，参考Markdown格式
1. 标注函数名称及行号，使用代码块复制修改部分的内容
2. 充分说明修改意见和理由
3. 友好交流
4. 在末尾注明评审人和时间

#### Review相关心理建设
1. 完成交接向前推进工作和相互激励多学习多提升是CodeReview的主题，一定要注意言辞，还有审核提意见的技巧
2. 如果有代码规范一类的问题，请push对方对着UECplusplus.md进行修改


