Param(
    [switch] $cpp,
    [switch] $cs,
    [switch] $java,
    [switch] $go)

$resnum = 4

$numbers = @(1, 10, 50, 100, 200, 500, 750, 1000, 1500, 2000)

$resources = Import-Csv -Delimiter ";" -Path ..\resources.csv

if ($cpp) {
    if (Test-Path Both\data_cpp.csv) {
        Remove-Item Both\data_cpp.csv
    }

    $i = 0
    foreach ($number in $numbers) {
	    Write-Progress -Activity "C++ matching" `
                       -CurrentOperation "String matching on file $($resources[$resnum].FileName) with word `"$($resources[$resnum].Word)`" for $($number) times" `
                       -PercentComplete $($i / 10 * 100)

	    ..\cpp\MatchableString\x64\Release\MatchableString.exe both $($resources[$resnum].FileName) "$($resources[$resnum].Word)" 1 $number | 
                                                     Out-File Both\data_cpp.csv -Append
        
        $i += 1
    }

    Write-Progress -Activity "C++ matching" -Completed
}

if ($cs) {
    if (Test-Path Both\data_cs.csv) {
        Remove-Item Both\data_cs.csv
    }

    $i = 0
    foreach ($number in $numbers) {
	    Write-Progress -Activity "C# matching" `
                       -CurrentOperation "String matching on file $($resources[$resnum].FileName) with word `"$($resources[$resnum].Word)`" for $($number) times" `
                       -PercentComplete $($i / 10 * 100)

	    ..\cs\MatchableString\MatchableString\bin\Release\MatchableString.exe both $($resources[$resnum].FileName) "$($resources[$resnum].Word)" 1 $number | 
                                                    Out-File Both\data_cs.csv -Append

        $i += 1
    }
}

if ($java) {
    if (Test-Path Both\data_java.csv) {
        Remove-Item Both\data_java.csv
    }

    $i = 0
    foreach ($number in $numbers) {
	    Write-Progress -Activity "Java matching" `
                       -CurrentOperation "String matching on file $($resources[$resnum].FileName) with word `"$($resources[$resnum].Word)`" for $($number) times" `
                       -PercentComplete $($i / 10 * 100)

	    java -cp ..\java\MatchableString\out\production\MatchableString matchablestring.Program both $($resources[$resnum].FileName) "$($resources[$resnum].Word)" 1 $number | 
                                                    Out-File Both\data_java.csv -Append
        
        $i += 1
    }
}

if ($go) {
    if (Test-Path Both\data_go.csv) {
        Remove-Item Both\data_go.csv
    }

    $i = 0
    foreach ($number in $numbers) {
	    Write-Progress -Activity "Go matching" `
                       -CurrentOperation "String matching on file $($resources[$resnum].FileName) with word `"$($resources[$resnum].Word)`" for $($number) times" `
                       -PercentComplete $($i / 10 * 100)

	    ..\go\MatchableString\MatchableString.exe both $($resources[$resnum].FileName) "$($resources[$resnum].Word)" 1 $number | 
                                                    Out-File Both\data_go.csv -Append
        
        $i += 1
    }
}

Write-Host -ForegroundColor Green "All measurements DONE."