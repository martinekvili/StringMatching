@echo off

echo. > data.csv

echo Starting measurement of string matching algorithms
echo.

set FILES=(bfranklin.txt, dostoyevsky.txt, jackrabbit.txt, napoleon.txt, dante.txt, spacewrecked.txt)
for %%f in %FILES% do (
	echo String matching on file %%f...
	StringMatch.exe %%f >> data.csv
	)