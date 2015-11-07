#include "matchablestrings.h"

std::unique_ptr<MatchableString> MatchableStrings::createBoyer(const std::string& s) {
	return std::make_unique<MatchableStringB>(s.data());
}

std::unique_ptr<MatchableString> MatchableStrings::createSuffixArray(const std::string& s) {
	return std::make_unique<MatchableStringSA>(s.data());
}