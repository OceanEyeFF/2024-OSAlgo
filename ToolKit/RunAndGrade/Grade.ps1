# 设置路径
$outDir = "./out"
$ansDir = "./ans"
$arguments = $args 
$resultFile = Join-Path -Path $PWD -ChildPath "result-$($args -join '-').txt"

Write-Host "Result File路径: $($resultFile -join ', ')"

# 检查 result.txt 是否存在，不存在则创建
if (-not (Test-Path $resultFile)) {
    New-Item -Path $resultFile -ItemType File | Out-Null
}

# 清空 result.txt 文件以准备新的输出
Clear-Content -Path $resultFile

# 初始化计数器
$totalCases = 0
$matchingCases = 0

# 获取所有 ans 文件
$ansFiles = Get-ChildItem -Path $ansDir -Filter "*.ans"

foreach ($ansFile in $ansFiles) {
    $caseName = [System.IO.Path]::GetFileNameWithoutExtension($ansFile.Name)
    $outFilePath = Join-Path -Path $outDir -ChildPath "$caseName.out"
    
    if (Test-Path $outFilePath) {
        $totalCases++
        
        # 读取文件内容
        $ansContent = Get-Content -Path $ansFile.FullName -Raw
        $outContent = Get-Content -Path $outFilePath -Raw
        
        # 比较内容
        if ($ansContent -ne $outContent) {
            # 输出不一致的文件名（去后缀）
            $result = "不一致的文件: $caseName"
            Write-Host $result
            Add-Content -Path $resultFile -Value $result
        } else {
            $matchingCases++
        }
    } else {
        # 处理缺少 .out 文件的情况
        $missingFileMessage = "缺少文件: $caseName.out"
        Write-Host $missingFileMessage
        Add-Content -Path $resultFile -Value $missingFileMessage
    }
}

# 输出总结果
$resultSummary = "$matchingCases/$totalCases"
Write-Host "一致的个数: $resultSummary"
Add-Content -Path $resultFile -Value "一致的个数: $resultSummary"
