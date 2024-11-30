#!/bin/bash

# 设置路径
outDir="./out"
ansDir="./ans"
arguments=("$@")
resultFile="$(pwd)/result-$(IFS=-; echo "${arguments[*]}").txt"

echo "Result File路径: $resultFile"

# 检查 result.txt 是否存在，不存在则创建
if [ ! -f "$resultFile" ]; then
    touch "$resultFile"
fi

# 清空 result.txt 文件以准备新的输出
> "$resultFile"

# 初始化计数器
totalCases=0
matchingCases=0

# 获取所有 ans 文件
ansFiles=("$ansDir"/*.ans)

for ansFile in "${ansFiles[@]}"; do
    caseName=$(basename "$ansFile" .ans)
    outFilePath="$outDir/$caseName.out"

    if [ -f "$outFilePath" ]; then
        totalCases=$((totalCases + 1))

        # 读取文件内容
        ansContent=$(< "$ansFile")
        outContent=$(< "$outFilePath")

        # 比较内容
        if [ "$ansContent" != "$outContent" ]; then
            # 输出不一致的文件名（去后缀）
            result="不一致的文件: $caseName"
            echo "$result"
            echo "$result" >> "$resultFile"
        else
            matchingCases=$((matchingCases + 1))
        fi
    else
        # 处理缺少 .out 文件的情况
        missingFileMessage="缺少文件: $caseName.out"
        echo "$missingFileMessage"
        echo "$missingFileMessage" >> "$resultFile"
    fi
done

# 输出总结果
resultSummary="$matchingCases/$totalCases"
echo "一致的个数: $resultSummary"
echo "一致的个数: $resultSummary" >> "$resultFile"
