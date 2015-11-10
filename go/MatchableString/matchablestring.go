package main

type MatchableString interface {
	SetString(s string)
	Preprocess(parallel bool)
	Match(pattern *Pattern, parallel bool) []int
}
