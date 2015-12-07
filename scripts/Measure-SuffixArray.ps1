Param(
    [switch] $cpp,
    [switch] $cs,
    [switch] $java,
    [switch] $go)

$resources = Import-Csv -Delimiter ";" -Path ..\resources.csv

if (-not (Test-Path SuffixArrayAlgorithm)) {
    New-Item -ItemType directory -Path SuffixArrayAlgorithm | Out-Null
}

if ($cpp) {
    if (Test-Path SuffixArrayAlgorithm\data_cpp.csv) {
        Remove-Item SuffixArrayAlgorithm\data_cpp.csv
    }

    $i = 0
    foreach ($resource in $resources) {
	    Write-Progress -Activity "C++ matching" `
                       -CurrentOperation "String matching on file $($resource.FileName) with word `"$($resource.Word)`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\cpp\MatchableString\x64\Release\MatchableString.exe suffixarray $($resource.FileName) "$($resource.Word)" 1 1 | 
                                                     Out-File SuffixArrayAlgorithm\data_cpp.csv -Append
        
        $i += 1
    }

    Write-Progress -Activity "C++ matching" -Completed
}

if ($cs) {
    if (Test-Path SuffixArrayAlgorithm\data_cs.csv) {
        Remove-Item SuffixArrayAlgorithm\data_cs.csv
    }

    $i = 0
    foreach ($resource in $resources) {
	    Write-Progress -Activity "C# matching" `
                       -CurrentOperation "String matching on file $($resource.FileName) with word `"$($resource.Word)`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\cs\MatchableString\MatchableString\bin\Release\MatchableString.exe suffixarray $($resource.FileName) "$($resource.Word)" 1 1 | 
                                                    Out-File SuffixArrayAlgorithm\data_cs.csv -Append

        $i += 1
    }
}

if ($java) {
    if (Test-Path SuffixArrayAlgorithm\data_java.csv) {
        Remove-Item SuffixArrayAlgorithm\data_java.csv
    }

    $i = 0
    foreach ($resource in $resources) {
	    Write-Progress -Activity "Java matching" `
                       -CurrentOperation "String matching on file $($resource.FileName) with word `"$($resource.Word)`"" `
                       -PercentComplete $($i / 6 * 100)

	    java -cp ..\java\MatchableString\out\production\MatchableString matchablestring.Program suffixarray $($resource.FileName) "$($resource.Word)" 1 1 | 
                                                    Out-File SuffixArrayAlgorithm\data_java.csv -Append
        
        $i += 1
    }
}

if ($go) {
    if (Test-Path SuffixArrayAlgorithm\data_go.csv) {
        Remove-Item SuffixArrayAlgorithm\data_go.csv
    }

    $i = 0
    foreach ($resource in $resources) {
	    Write-Progress -Activity "Go matching" `
                       -CurrentOperation "String matching on file $($resource.FileName) with word `"$($resource.Word)`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\go\MatchableString\MatchableString.exe suffixarray $($resource.FileName) "$($resource.Word)" 1 1 | 
                                                    Out-File SuffixArrayAlgorithm\data_go.csv -Append
        
        $i += 1
    }
}

Write-Host -ForegroundColor Green "All measurements DONE."