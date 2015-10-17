@echo off

go build -o BoyerAlgorithm.exe program.go pattern.go match.go

if %errorlevel% equ 0 gofmt -w program.go pattern.go match.go