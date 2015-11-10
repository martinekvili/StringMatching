package main

import "container/list"

type MatchableStringB struct {
	str    string
	length int
}

func (s *MatchableStringB) SetString(str string) {
	s.str = str
	s.length = len(str)
}

func (s *MatchableStringB) Preprocess(parallel bool) {}

func findFirst(str string, pat *Pattern) int {
	i := pat.length - 1
	strlen := len(str)

	for i < strlen {
		j := pat.length - 1
		for ; j >= 0; j-- {
			if str[i] != pat.str[j] {
				break
			}
			i--
		}
		if j < 0 {
			return i + 1
		} else {
			if pat.delta1[str[i]] > pat.delta2[j] {
				i += pat.delta1[str[i]]
			} else {
				i += pat.delta2[j]
			}
		}
	}

	return -1
}

func matchSubstr(str string, pat *Pattern, startPos int) (occurrences list.List) {
	occ := 0
	next := findFirst(str[occ:], pat)

	for next != -1 {
		occ += next
		occurrences.PushBack(occ + startPos)
		occ++
		next = findFirst(str[occ:], pat)
	}

	return
}

func matchSubstr_(str string, pat *Pattern, strlen int, i int,
	parts int, occurrencesArray []list.List, ch chan int) {
	var subStr string
	if i < parts-1 {
		subStr = str[i*strlen/parts : (i+1)*strlen/parts+pat.length-1]
	} else {
		subStr = str[i*strlen/parts:]
	}
	occurrencesArray[i] = matchSubstr(subStr, pat, i*strlen/parts)
	ch <- occurrencesArray[i].Len()
}

func (s *MatchableStringB) Match(pat *Pattern, parallel bool) []int {
	if !pat.isPreprocessed {
		pat.Preprocess()
	}

	parts := 8

	size := 0
	occurrencesArray := make([]list.List, parts)

	if !parallel {
		for i := 0; i < parts; i++ {
			var subStr string
			if i < parts-1 {
				subStr = s.str[i*s.length/parts : (i+1)*s.length/parts+pat.length-1]
			} else {
				subStr = s.str[i*s.length/parts:]
			}
			occurrencesArray[i] = matchSubstr(subStr, pat, i*s.length/parts)
			size += occurrencesArray[i].Len()
		}
	} else {
		ch := make(chan int)

		for i := 0; i < parts; i++ {
			go matchSubstr_(s.str, pat, s.length, i, parts, occurrencesArray, ch)
		}

		for i := 0; i < parts; i++ {
			size += <-ch
		}
	}

	occurrences := make([]int, size)
	j := 0
	for i := 0; i < parts; i++ {
		for e := occurrencesArray[i].Front(); e != nil; e = e.Next() {
			occurrences[j] = e.Value.(int)
			j++
		}
	}

	return occurrences
}
