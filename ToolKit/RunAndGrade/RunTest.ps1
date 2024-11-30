# ���ø�Ŀ¼���ļ���·��
$rootDir = Get-Location
$inDir = Join-Path $rootDir "in"
$outDir = Join-Path $rootDir "out"
$ansDir = Join-Path $rootDir "ans"
$exeFile = Join-Path $rootDir "Main.exe"

# ��ӡ����Ĳ���
$arguments = $args  # ������Ĳ����洢������

# ����Ƿ�ֻ����һ������
if ($arguments.Count -ne 1) {
    Write-Host "��ֻ����һ��������"
    exit
}

# ���� $arguments.txt �ļ�
$argFile = Join-Path $rootDir "$($arguments[0]).txt"
if (-not (Test-Path $argFile)) {
    New-Item -ItemType File -Path $argFile | Out-Null
    Write-Host "$argFile �ļ��Ѵ�����"
}


# 1. ��鲢���� ./out �ļ���
if (-not (Test-Path $outDir)) {
    New-Item -ItemType Directory -Path $outDir
}

# 2. ��˳���� ./in �ļ����е�ÿ�� .in �ļ�
Get-ChildItem -Path $inDir -Filter "*.in" | Sort-Object Name | ForEach-Object {
    $inputFile = $_
    $inputFileName = $inputFile.Name -replace "\.in$", ""  # ��ȡ�ļ�����������չ����

    # �� $argFile ��д�뱾�ֲ��Ե��ļ�����ȥ��׺��
    Add-Content -Path $argFile -Value $inputFileName

    # a. �����ļ�����Ŀ¼��������Ϊ CASE.in
    $caseInFile = Join-Path $rootDir "CASE.in"
    Copy-Item -Path $inputFile.FullName -Destination $caseInFile

	# ��ӡִ�в���
    Write-Host "ִ�� Main.exe �Ĳ���: $($arguments -join ', ')"

    # ִ�� Main.exe�����������
    $caseOutFile = Join-Path $rootDir "CASE.out"
	Start-Process -FilePath $exeFile -ArgumentList $arguments -Wait -NoNewWindow -ErrorAction SilentlyContinue

    # b. �������ļ����ڣ����Ƶ� ./out �ļ���
    if (Test-Path $caseOutFile) {
        $outputFileName = "$inputFileName.out"
        $outputFile = Join-Path $outDir $outputFileName
        Copy-Item -Path $caseOutFile -Destination $outputFile
    }

    # c. ɾ����Ŀ¼�µ� CASE.in �� CASE.out �ļ�
    Remove-Item -Path $caseInFile -Force
    if (Test-Path $caseOutFile) {
        Remove-Item -Path $caseOutFile -Force
    }
}

Write-Host "$arguments ���в�����ɡ�"
