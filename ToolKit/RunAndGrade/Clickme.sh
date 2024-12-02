#!/bin/bash

# 检查是否有传入参数
if [ "$#" -eq 0 ]; then
    echo "没有传入参数，使用默认参数: FIFO LRU CLOCK IMPROVEDCLOCK"
    commands=("FIFO" "LRU" "CLOCK" "IMPROVEDCLOCK")
else
    # 记录参数的数组
    commands=("$@")
fi

# 检查并创建 ./bin 文件夹
binDir="./bin"
if [ ! -d "$binDir" ]; then
    mkdir "$binDir"
fi

# 根据 commands 数组中的元素数量来运行步骤
for command in "${commands[@]}"; do
    # 执行 RunTest.sh
    ./RunTest.sh "$command"
    if [ $? -ne 0 ]; then
        echo "RunTest.sh 执行失败，命令: $command"
        continue
    fi

    # 执行 Grade.sh
    ./Grade.sh "$command"
    if [ $? -ne 0 ]; then
        echo "Grade.sh 执行失败，命令: $command"
        continue
    fi

    # 检查 ./out 文件夹是否存在
    outDir="./out"
    if [ -d "$outDir" ]; then
        # 重命名 ./out 文件夹为 ./out-<command>
        newOutDir="./out-$command"
        mv "$outDir" "$newOutDir"
    fi

    # 移动所有的 *-out 文件夹和 *.txt 文件到 ./bin 目录下
    mv out-* "$binDir/" 2>/dev/null
    mv *.txt "$binDir/" 2>/dev/null
    mv *.csv "$binDir/" 2>/dev/null
done

echo "所有命令已执行完毕。"
