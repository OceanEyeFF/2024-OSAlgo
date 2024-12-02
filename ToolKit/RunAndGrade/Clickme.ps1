# 检查是否有传入参数
if ($args.Count -eq 0) {
    Write-Host "没有传入参数，使用默认参数: FIFO LRU CLOCK IMPROVEDCLOCK"
    $Commands = @("FIFO", "LRU", "CLOCK", "IMPROVEDCLOCK")
} else {
    # 记录参数的字符串数组
    $Commands = @($args)
}

# 检查并创建 ./bin 文件夹
$binDir = Join-Path -Path $PWD -ChildPath "bin"
if (-not (Test-Path $binDir)) {
	New-Item -Path $binDir -ItemType Directory | Out-Null
}

# 根据 $Commands 中字符串数量来运行步骤
for ($i = 0; $i -lt $Commands.Count; $i++) {
    # 执行 RunTest.ps1
    $runTestResult = Start-Process -FilePath "powershell.exe" -ArgumentList "-File `"$PWD\RunTest.ps1`" `"$($Commands[$i])`"" -Wait -NoNewWindow

    # 执行 Grade.ps1
    $gradeResult = Start-Process -FilePath "powershell.exe" -ArgumentList "-File `"$PWD\Grade.ps1`" `"$($Commands[$i])`"" -Wait -NoNewWindow

    # 检查 ./out 文件夹是否存在
    $outDir = Join-Path -Path $PWD -ChildPath "out"
    if (Test-Path $outDir) {
        # 重命名 ./out 文件夹为 ./out-$($Commands[$i])
        $newOutDir = Join-Path -Path $PWD -ChildPath "out-$($Commands[$i])"
        Rename-Item -Path $outDir -NewName $newOutDir
    }

    # 移动所有的 *-out 文件夹和 *.txt 文件到 ./bin 目录下
    Get-ChildItem -Path "$PWD\out-*", "$PWD\*.txt", "$PWD\*.csv" | Move-Item -Destination $binDir -Force
}

Write-Host "所有命令已执行完毕。"
