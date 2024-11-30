#!/bin/bash

# 设置根目录和文件夹路径
rootDir=$(pwd)
inDir="$rootDir/in"
outDir="$rootDir/out"
ansDir="$rootDir/ans"
exeFile="$rootDir/Main"

# 打印传入的参数
arguments=("$@")  # 将传入的参数存储到数组


# 检查是否只传入一个参数
if [ "${#arguments[@]}" -ne 1 ]; then
    echo "请只传入一个参数。"
    exit 1
fi

# 创建 $arguments.txt 文件
argFile="$rootDir/${arguments[0]}.txt"
if [ ! -f "$argFile" ]; then
    touch "$argFile"
    echo "$argFile 文件已创建。"
fi

# 1. 检查并创建 ./out 文件夹
if [ ! -d "$outDir" ]; then
    mkdir "$outDir"
fi


# 2. 按顺序处理 ./in 文件夹中的每个 .in 文件
for inputFile in "$inDir"/*.in; do
    inputFileName=$(basename "$inputFile" .in)  # 获取文件名（不带扩展名）

    # 在 $argFile 中写入本轮测试的文件名（去后缀）
    echo "$inputFileName" >> "$argFile"

    # a. 复制文件到根目录并重命名为 CASE.in
    caseInFile="$rootDir/CASE.in"
    cp "$inputFile" "$caseInFile"

    # 打印执行参数
    echo "执行 Main.exe 的参数: ${arguments[*]}"

    # 执行 Main.exe，并捕获错误
    caseOutFile="$rootDir/CASE.out"
    "$exeFile" "${arguments[@]}" > /dev/null 2>&1

    # b. 如果输出文件存在，则复制到 ./out 文件夹
    if [ -f "$caseOutFile" ]; then
        outputFileName="$inputFileName.out"
        outputFile="$outDir/$outputFileName"
        cp "$caseOutFile" "$outputFile"
    fi

    # c. 删除根目录下的 CASE.in 和 CASE.out 文件
    rm -f "$caseInFile"
    if [ -f "$caseOutFile" ]; then
        rm -f "$caseOutFile"
    fi
done

echo "${arguments[*]} 运行测试完成。"
