Param(
    [switch] $cpp,
    [switch] $cs,
    [switch] $java,
    [switch] $go)

$multiplier = 16
$num = 50

$resources = Import-Csv -Delimiter ";" -Path ..\resources.csv

if ($cpp) {
    if (Test-Path BoyerAlgorithm\data_cpp.csv) {
        Remove-Item BoyerAlgorithm\data_cpp.csv
    }

    $i = 0
    foreach ($resource in $resources) {
	    Write-Progress -Activity "C++ matching" `
                       -CurrentOperation "String matching on file $($resource.FileName) with word `"$($resource.Word)`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\cpp\MatchableString\x64\Release\MatchableString.exe boyer $($resource.FileName) "$($resource.Word)" $multiplier $num | 
                                                     Out-File BoyerAlgorithm\data_cpp.csv -Append
        
        $i += 1
    }

    Write-Progress -Activity "C++ matching" -Completed
}

if ($cs) {
    if (Test-Path BoyerAlgorithm\data_cs.csv) {
        Remove-Item BoyerAlgorithm\data_cs.csv
    }

    $i = 0
    foreach ($resource in $resources) {
	    Write-Progress -Activity "C# matching" `
                       -CurrentOperation "String matching on file $($resource.FileName) with word `"$($resource.Word)`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\cs\MatchableString\MatchableString\bin\Release\MatchableString.exe boyer $($resource.FileName) "$($resource.Word)" $multiplier $num | 
                                                    Out-File BoyerAlgorithm\data_cs.csv -Append

        $i += 1
    }
}

if ($java) {
    if (Test-Path BoyerAlgorithm\data_java.csv) {
        Remove-Item BoyerAlgorithm\data_java.csv
    }

    $i = 0
    foreach ($resource in $resources) {
	    Write-Progress -Activity "Java matching" `
                       -CurrentOperation "String matching on file $($resource.FileName) with word `"$($resource.Word)`"" `
                       -PercentComplete $($i / 6 * 100)

	    java -cp ..\java\BoyerAlgorithm\bin\ boyer.Program $($resource.FileName) "$($resource.Word)" $multiplier $num | 
                                                    Out-File BoyerAlgorithm\data_java.csv -Append
        
        $i += 1
    }
}

if ($go) {
    if (Test-Path BoyerAlgorithm\data_go.csv) {
        Remove-Item BoyerAlgorithm\data_go.csv
    }

    $i = 0
    foreach ($resource in $resources) {
	    Write-Progress -Activity "Go matching" `
                       -CurrentOperation "String matching on file $($resource.FileName) with word `"$($resource.Word)`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\go\BoyerAlgorithm\BoyerAlgorithm.exe $($resource.FileName) "$($resource.Word)" $multiplier $num | 
                                                    Out-File BoyerAlgorithm\data_go.csv -Append
        
        $i += 1
    }
}

Write-Host -ForegroundColor Green "All measurements DONE."