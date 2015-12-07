#include "matchablestrings.h"

std::unique_ptr<MatchableString> MatchableStrings::createBoyer(const char *s) {
	return std::make_unique<MatchableStringB>(s);
}

std::unique_ptr<MatchableString> MatchableStrings::createSuffixArray(const char *s) {
	return std::make_unique<MatchableStringSA>(s);
}

std::unique_ptr<MatchableString> MatchableStrings::create(const char *s, NumberOfMatches approx) {
	switch (approx) {
	case LessThan1000:
		return std::make_unique<MatchableStringB>(s);
	case MoreThan1000:
		return std::make_unique<MatchableStringSA>(s);
	}
}