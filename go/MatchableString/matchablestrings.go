package main

type NumberOfMatches int

const (
	LessThan1000 NumberOfMatches = iota
	MoreThan1000
)

func createBoyer(str string) MatchableString {
	var boyer MatchableStringB
	boyer.SetString(str)

	return &boyer
}

func createSuffixArray(str string) MatchableString {
	var suffixarray MatchableStringSA
	suffixarray.SetString(str)

	return &suffixarray
}

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
