#!/bin/bash

# 检查是否有传入参数
if [ "$#" -eq 0 ]; then
    echo "请提供至少一个参数。"
    exit 1
fi

# 记录参数的数组
commands=("$@")

# 检查并创建 ./bin 文件夹
binDir="$PWD/bin"
if [ ! -d "$binDir" ]; then
    mkdir "$binDir"
fi

# 根据 commands 数组中的元素数量来运行步骤
for command in "${commands[@]}"; do
    # 执行 RunTest.sh
    pwsh -File "$PWD/RunTest.ps1" "$command"

    # 执行 Grade.sh
    pwsh -File "$PWD/Grade.ps1" "$command"

    # 检查 ./out 文件夹是否存在
    outDir="$PWD/out"
    if [ -d "$outDir" ]; then
        # 重命名 ./out 文件夹为 ./out-$command
        newOutDir="$PWD/out-$command"
        mv "$outDir" "$newOutDir"
    fi

    # 移动所有的 *-out 文件夹和 *.txt 文件到 ./bin 目录下
    mv "$PWD/out-"* "$binDir/" 2>/dev/null
    mv "$PWD/"*.txt "$binDir/" 2>/dev/null
done

echo "所有命令已执行完毕。"
