Param(
    [switch] $cpp,
    [switch] $cs,
    [switch] $java,
    [switch] $go)


$files = ("bfranklin.txt", "dostoyevsky.txt", "jackrabbit.txt", "napoleon.txt", "dante.txt", "spacewrecked.txt")

#$words = ( "fire mixed with water", "significant object at", "rappers from the rose",
#               "almost immediately be", "ow a corpse they left", "retreat into the bush")

$words = ("contiguity", "hereditary", "smithereen", "expressive", "forfeiture", "plentifull")

if ($cpp) {
    if (Test-Path data_cpp.csv) {
        Remove-Item data_cpp.csv
    }

    for ($i = 0; $i -lt 6; $i += 1) {
	    Write-Progress -Activity "C++ matching" `
                       -CurrentOperation "String matching on file $($files[$i]) with word `"$($words[$i])`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\cpp\BoyerAlgorithm\x64\Release\BoyerAlgorithm.exe $($files[$i]) "$($words[$i])" | 
                                                     Out-File data_cpp.csv -Append
    }

    Write-Progress -Activity "C++ matching" -Completed
}

if ($cs) {
    if (Test-Path data_cs.csv) {
        Remove-Item data_cs.csv
    }

    for ($i = 0; $i -lt 6; $i += 1) {
	    Write-Progress -Activity "C# matching" `
                       -CurrentOperation "String matching on file $($files[$i]) with word `"$($words[$i])`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\cs\BoyerAlgorithm\BoyerAlgorithm\bin\Release\BoyerAlgorithm.exe $($files[$i]) "$($words[$i])" | 
                                                    Out-File data_cs.csv -Append
    }
}

if ($java) {
    if (Test-Path data_java.csv) {
        Remove-Item data_java.csv
    }

    for ($i = 0; $i -lt 6; $i += 1) {
	    Write-Progress -Activity "Java matching" `
                       -CurrentOperation "String matching on file $($files[$i]) with word `"$($words[$i])`"" `
                       -PercentComplete $($i / 6 * 100)

	    java -cp ..\java\BoyerAlgorithm\bin\ boyer.Program $($files[$i]) "$($words[$i])" | 
                                                    Out-File data_java.csv -Append
    }
}

if ($go) {
    if (Test-Path data_go.csv) {
        Remove-Item data_go.csv
    }

    for ($i = 0; $i -lt 6; $i += 1) {
	    Write-Progress -Activity "Go matching" `
                       -CurrentOperation "String matching on file $($files[$i]) with word `"$($words[$i])`"" `
                       -PercentComplete $($i / 6 * 100)

	    ..\go\BoyerAlgorithm\BoyerAlgorithm.exe $($files[$i]) "$($words[$i])" | 
                                                    Out-File data_go.csv -Append
	    }
}

Write-Host -ForegroundColor Green "All measurements DONE."