#ifndef MATCHABLESTRING_H_INCLUDED
#define MATCHABLESTRING_H_INCLUDED

#include <list>
#include <vector>

#include "tbb\blocked_range.h"
#include "tbb\parallel_for.h"

#include "pattern.h"

class MatchAbleString {
    char *str;
    int length;

    static int findFirst(const Pattern &p, const char *str, size_t length);
	static std::vector<int>* matchSubstr(const Pattern &p, const char *str_, int length_, int startPos);

	std::vector<int>* matchSubstr(const Pattern &p, int parts, int i);

public:
    MatchAbleString(const char *c);
    ~MatchAbleString();

	MatchAbleString(const MatchAbleString&) = delete;
	MatchAbleString& operator=(const MatchAbleString&) = delete;

	std::vector<int> match(const Pattern &p, bool parallel = false);
};

#endif // MATCHABLESTRING_H_INCLUDED
