# 设置根目录和文件夹路径
$rootDir = Get-Location
$inDir = Join-Path $rootDir "in"
$outDir = Join-Path $rootDir "out"
$ansDir = Join-Path $rootDir "ans"
$exeFile = Join-Path $rootDir "Main.exe"

# 1. 检查并创建 ./out 文件夹
if (-not (Test-Path $outDir)) {
    New-Item -ItemType Directory -Path $outDir
}

# 2. 按顺序处理 ./in 文件夹中的每个 .in 文件
Get-ChildItem -Path $inDir -Filter "*.in" | Sort-Object Name | ForEach-Object {
    $inputFile = $_
    $inputFileName = $inputFile.Name -replace "\.in$", ""  # 获取文件名（不带扩展名）

    # a. 复制文件到根目录并重命名为 CASE.in
    $caseInFile = Join-Path $rootDir "CASE.in"
    Copy-Item -Path $inputFile.FullName -Destination $caseInFile

    # b. 执行 Main.exe，并捕获错误
    $caseOutFile = Join-Path $rootDir "CASE.out"
    Start-Process -FilePath $exeFile -ArgumentList $caseInFile -Wait -NoNewWindow -ErrorAction SilentlyContinue

    # c. 如果输出文件存在，则复制到 ./out 文件夹
    if (Test-Path $caseOutFile) {
        $outputFileName = "$inputFileName.out"
        $outputFile = Join-Path $outDir $outputFileName
        Copy-Item -Path $caseOutFile -Destination $outputFile
    }

    # d. 删除根目录下的 CASE.in 和 CASE.out 文件
    Remove-Item -Path $caseInFile -Force
    if (Test-Path $caseOutFile) {
        Remove-Item -Path $caseOutFile -Force
    }
}

Write-Host "处理完成。"
