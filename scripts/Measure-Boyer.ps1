Param(
    [switch] $cpp,
    [switch] $cs,
    [switch] $java,
    [switch] $go)

$multiplier = 1280
$num = 50

$files = ("bfranklin.txt", "dostoyevsky.txt", "jackrabbit.txt", "napoleon.txt", "dante.txt", "spacewrecked.txt")

#$words = ( "fire mixed with water", "significant object at", "rappers from the rose",
#               "almost immediately be", "ow a corpse they left", "retreat into the bush")

$words = ("contiguity", "hereditary", "smithereen", "expressive", "forfeiture", "plentifull")

if ($cpp) {
    if (Test-Path BoyerAlgorithm\data_cpp.csv) {
        Remove-Item BoyerAlgorithm\data_cpp.csv
    }

    for ($i = 0; $i -lt 6; $i += 1) {
	    Write-Progress -Activity "C++ matching" `
                       -CurrentOperation "String matching on file $($files[$i]) with word `"$($words[$i])`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\cpp\BoyerAlgorithm\x64\Release\BoyerAlgorithm.exe $($files[$i]) "$($words[$i])" $multiplier $num | 
                                                     Out-File BoyerAlgorithm\data_cpp.csv -Append
    }

    Write-Progress -Activity "C++ matching" -Completed
}

if ($cs) {
    if (Test-Path BoyerAlgorithm\data_cs.csv) {
        Remove-Item BoyerAlgorithm\data_cs.csv
    }

    for ($i = 0; $i -lt 6; $i += 1) {
	    Write-Progress -Activity "C# matching" `
                       -CurrentOperation "String matching on file $($files[$i]) with word `"$($words[$i])`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\cs\BoyerAlgorithm\BoyerAlgorithm\bin\Release\BoyerAlgorithm.exe $($files[$i]) "$($words[$i])" $multiplier $num | 
                                                    Out-File BoyerAlgorithm\data_cs.csv -Append
    }
}

if ($java) {
    if (Test-Path BoyerAlgorithm\data_java.csv) {
        Remove-Item BoyerAlgorithm\data_java.csv
    }

    for ($i = 0; $i -lt 6; $i += 1) {
	    Write-Progress -Activity "Java matching" `
                       -CurrentOperation "String matching on file $($files[$i]) with word `"$($words[$i])`"" `
                       -PercentComplete $($i / 6 * 100)

	    java -cp ..\java\BoyerAlgorithm\bin\ boyer.Program $($files[$i]) "$($words[$i])" $multiplier $num | 
                                                    Out-File BoyerAlgorithm\data_java.csv -Append
    }
}

if ($go) {
    if (Test-Path BoyerAlgorithm\data_go.csv) {
        Remove-Item BoyerAlgorithm\data_go.csv
    }

    for ($i = 0; $i -lt 6; $i += 1) {
	    Write-Progress -Activity "Go matching" `
                       -CurrentOperation "String matching on file $($files[$i]) with word `"$($words[$i])`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\go\BoyerAlgorithm\BoyerAlgorithm.exe $($files[$i]) "$($words[$i])" $multiplier $num | 
                                                    Out-File BoyerAlgorithm\data_go.csv -Append
	    }
}

Write-Host -ForegroundColor Green "All measurements DONE."