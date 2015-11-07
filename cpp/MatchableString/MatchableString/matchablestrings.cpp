#include "matchablestrings.h"

std::unique_ptr<MatchableString> MatchableStrings::createBoyer(const char *s) {
	return std::make_unique<MatchableStringB>(s);
}

std::unique_ptr<MatchableString> MatchableStrings::createSuffixArray(const char *s) {
	return std::make_unique<MatchableStringSA>(s);
}