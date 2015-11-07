#ifndef MATCHABLESTRINGS_H
#define MATCHABLESTRINGS_H

#include <memory>
#include <string>

#include "matchablestring.h"
#include "boyer\matchablestringb.h"
#include "suffixarray\matchablestringsa.h"

class MatchableStrings {
public:
	static std::unique_ptr<MatchableString> createBoyer(const char *s);
	static std::unique_ptr<MatchableString> createSuffixArray(const char *s);
};

#endif