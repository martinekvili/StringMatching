@echo off

echo ;1;2;4;8;16;32;64; > data.csv

echo Starting measurement of parallel sorting algorithms
echo.

set SIZES=(2000000 5000000 10000000 15000000 20000000 40000000)
for %%i in %SIZES% do (
	echo Measurement on array of %%i integers...
	ParallelSort2.exe %%i >> data.csv
	)