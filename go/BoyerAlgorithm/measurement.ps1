Clear-Content data.csv

Write-Output("Starting measurement of string matching algorithms")
Write-Output("")

$files = ("bfranklin.txt", "dostoyevsky.txt", "jackrabbit.txt", "napoleon.txt", "dante.txt", "spacewrecked.txt")

$words = ( "fire mixed with water", "significant object at", "rappers from the rose",
               "almost immediately be", "ow a corpse they left", "retreat into the bush")

#$words = ("contiguity", "hereditary", "smithereen", "expressive", "adversary", "plentifully")

for ($i = 0; $i -lt 6; $i += 1) {
	Write-Output("String matching on file $($files[$i]) with word $($words[$i])...")
	.\BoyerAlgorithm.exe $($files[$i]) "$($words[$i])" | Out-File data.csv -Append
	}