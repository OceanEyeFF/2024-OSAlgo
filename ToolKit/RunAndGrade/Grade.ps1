# ����·��
$outDir = "./out"
$ansDir = "./ans"
$arguments = $args 
$resultFile = Join-Path -Path $PWD -ChildPath "result-$($args -join '-').txt"

Write-Host "Result File·��: $($resultFile -join ', ')"

# ��� result.txt �Ƿ���ڣ��������򴴽�
if (-not (Test-Path $resultFile)) {
    New-Item -Path $resultFile -ItemType File | Out-Null
}

# ��� result.txt �ļ���׼���µ����
Clear-Content -Path $resultFile

# ��ʼ��������
$totalCases = 0
$matchingCases = 0

# ��ȡ���� ans �ļ�
$ansFiles = Get-ChildItem -Path $ansDir -Filter "*.ans"

foreach ($ansFile in $ansFiles) {
    $caseName = [System.IO.Path]::GetFileNameWithoutExtension($ansFile.Name)
    $outFilePath = Join-Path -Path $outDir -ChildPath "$caseName.out"
    
    if (Test-Path $outFilePath) {
        $totalCases++
        
        # ��ȡ�ļ�����
        $ansContent = Get-Content -Path $ansFile.FullName -Raw
        $outContent = Get-Content -Path $outFilePath -Raw
        
        # �Ƚ�����
        if ($ansContent -ne $outContent) {
            # �����һ�µ��ļ�����ȥ��׺��
            $result = "��һ�µ��ļ�: $caseName"
            Write-Host $result
            Add-Content -Path $resultFile -Value $result
        } else {
            $matchingCases++
        }
    } else {
        # ����ȱ�� .out �ļ������
        $missingFileMessage = "ȱ���ļ�: $caseName.out"
        Write-Host $missingFileMessage
        Add-Content -Path $resultFile -Value $missingFileMessage
    }
}

# ����ܽ��
$resultSummary = "$matchingCases/$totalCases"
Write-Host "һ�µĸ���: $resultSummary"
Add-Content -Path $resultFile -Value "һ�µĸ���: $resultSummary"
