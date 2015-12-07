@echo off

go build -o MatchableString.exe program.go matchablestring.go matchablestrings.go pattern.go mergesort.go comparers.go matchablestringsa.go matchablestringb.go

if %errorlevel% equ 0 gofmt -w program.go matchablestring.go matchablestrings.go pattern.go mergesort.go comparers.go matchablestringsa.go matchablestringb.go