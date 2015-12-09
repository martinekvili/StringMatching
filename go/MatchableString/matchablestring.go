package main

type MatchableString interface {
	SetString(s string)

	// Preprocesses the main text, has to be called before the first matching.
	Preprocess(parallel bool)

	// Matches the given pattern on the string.
	// Returns the list of the occurrences.
	Match(pattern *Pattern, parallel bool) []int
}
