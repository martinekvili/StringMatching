#ifndef MATCHABLESTRING_H_INCLUDED
#define MATCHABLESTRING_H_INCLUDED

#include <vector>
#include <memory>

#include "tbb\blocked_range.h"
#include "tbb\parallel_for.h"

#include "pattern.h"

class MatchAbleString {
    std::string str;

    int findFirst(const Pattern &p, int startPos, int endPos);
	std::unique_ptr<std::vector<int>> _matchSubstr(const Pattern &p, int startPos, int endPos);
	std::unique_ptr<std::vector<int>> matchSubstr(const Pattern &p, int parts, int i);

public:
	MatchAbleString(std::string s) : str(s)  {}

	MatchAbleString(const MatchAbleString&) = delete;
	MatchAbleString& operator=(const MatchAbleString&) = delete;

	std::unique_ptr<std::vector<int>> match(const Pattern &p, bool parallel = false);
};

#endif // MATCHABLESTRING_H_INCLUDED
