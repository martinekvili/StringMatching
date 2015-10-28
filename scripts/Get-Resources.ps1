﻿$resources = Import-Csv -Delimiter ";" -Path ..\resources.csv

ForEach ($resource in $resources) {
    $fileName = "..\resources\" + $resource.FileName

    Invoke-WebRequest -Uri $resource.WebAddress -OutFile $fileName
}

