@echo off
setlocal EnableDelayedExpansion

echo. > data.csv

echo Starting measurement of string matching algorithms
echo.

set FILES=(bfranklin.txt, dostoyevsky.txt, jackrabbit.txt, napoleon.txt, dante.txt, spacewrecked.txt)
set WORDS=(contiguity, hereditary, knapsack, expressive, adversary, plentifully)
for /L %%i in (1, 1, 5) do (
	echo String matching on file !FILES[%%i]! with word !WORDS[%%i]!...
REM	BoyerAlgorithm.exe %FILES[%i%]% %WORDS[%i%]% >> data.csv
	)