package main

// Choices for the approximate number of matches.
type NumberOfMatches int

const (
	// This object will be used for less than 1000 matches.
	LessThan1000 NumberOfMatches = iota

	//This object will be used for more than 1000 matches.
	MoreThan1000
)

// Creates a matchable string object using Boyer-Moore algorithm.
func createBoyer(str string) MatchableString {
	var boyer MatchableStringB
	boyer.SetString(str)

	return &boyer
}

//  Creates a matchable string object using Suffix Array algorithm.
func createSuffixArray(str string) MatchableString {
	var suffixarray MatchableStringSA
	suffixarray.SetString(str)

	return &suffixarray
}

// Creates a matchable string object with a suitable implementation.
// approx is the approximate number of uses.
func create(str string, approx NumberOfMatches) MatchableString {
	switch approx {
	case LessThan1000:
		return createBoyer(str)
	case MoreThan1000:
		return createSuffixArray(str)
	default:
		return nil
	}
}
