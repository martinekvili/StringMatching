@echo off

echo. > data2.csv

echo Starting measurement of string matching algorithms
echo.

set SIZES=(0, 100, 200, 500, 1000, 2000, 5000, 10000, 15000, 20000)
for %%s in %SIZES% do (
	echo String matching with number of %%s...
	StringMatch.exe bfranklin.txt contiguity %%s >> data2.csv
	)