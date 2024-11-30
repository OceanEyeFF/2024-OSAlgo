# ����Ƿ��д������
if ($args.Count -eq 0) {
    Write-Host "û�д��������ʹ��Ĭ�ϲ���: FIFO LRU CLOCK IMPROVEDCLOCK"
    $Commands = @("FIFO", "LRU", "CLOCK", "IMPROVEDCLOCK")
} else {
    # ��¼�������ַ�������
    $Commands = @($args)
}

# ��鲢���� ./bin �ļ���
$binDir = Join-Path -Path $PWD -ChildPath "bin"
if (-not (Test-Path $binDir)) {
	New-Item -Path $binDir -ItemType Directory | Out-Null
}

# ���� $Commands ���ַ������������в���
for ($i = 0; $i -lt $Commands.Count; $i++) {
    # ִ�� RunTest.ps1
    $runTestResult = Start-Process -FilePath "powershell.exe" -ArgumentList "-File `"$PWD\RunTest.ps1`" `"$($Commands[$i])`"" -Wait -NoNewWindow

    # ִ�� Grade.ps1
    $gradeResult = Start-Process -FilePath "powershell.exe" -ArgumentList "-File `"$PWD\Grade.ps1`" `"$($Commands[$i])`"" -Wait -NoNewWindow

    # ��� ./out �ļ����Ƿ����
    $outDir = Join-Path -Path $PWD -ChildPath "out"
    if (Test-Path $outDir) {
        # ������ ./out �ļ���Ϊ ./out-$($Commands[$i])
        $newOutDir = Join-Path -Path $PWD -ChildPath "out-$($Commands[$i])"
        Rename-Item -Path $outDir -NewName $newOutDir
    }

    # �ƶ����е� *-out �ļ��к� *.txt �ļ��� ./bin Ŀ¼��
    Get-ChildItem -Path "$PWD\out-*", "$PWD\*.txt" | Move-Item -Destination $binDir -Force
}

Write-Host "����������ִ����ϡ�"