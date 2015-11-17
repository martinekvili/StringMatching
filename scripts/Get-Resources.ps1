If (-Not (Test-Path ..\resources)) {
    New-Item ..\resources -ItemType Directory | Out-Null
}

Invoke-WebRequest -Uri http://www.ibiblio.org/pub/docs/books/gutenberg/1/11/11.txt -OutFile "..\resources\00_alice.txt"

$resources = Import-Csv -Delimiter ";" -Path ..\resources.csv

ForEach ($resource in $resources) {
    $fileName = "..\resources\" + $resource.FileName

    Invoke-WebRequest -Uri $resource.WebAddress -OutFile $fileName
}

