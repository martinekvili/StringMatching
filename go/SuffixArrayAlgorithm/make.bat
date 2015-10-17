@echo off

go build -o SuffixArrayAlgorithm.exe program.go mergesort.go comparers.go matchablestring.go

if %errorlevel% equ 0 gofmt -w program.go mergesort.go comparers.go matchablestring.go