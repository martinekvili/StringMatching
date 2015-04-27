#ifndef MATCHABLESTRING_H_INCLUDED
#define MATCHABLESTRING_H_INCLUDED

#include <list>
#include <vector>

#include "tbb\blocked_range.h"
#include "tbb\parallel_for.h"

#include "pattern.h"

class MatchAbleString {
    char *str;
    size_t length;

    MatchAbleString(const MatchAbleString&);
    MatchAbleString& operator=(const MatchAbleString&);

    static int findFirst(Pattern &p, const char *str, size_t length);
	static std::list<int> matchSubstr(Pattern &p, const char *str_, int length_, int startPos);

	std::list<int> matchSubstr(Pattern &p, int parts, int i);

public:
    MatchAbleString(const char *c);
    ~MatchAbleString();

	std::list<int> match(Pattern &p, bool parallel = false);

	class ParallelMatcher {
		MatchAbleString &mas;
		Pattern &p;
		std::vector<std::list<int>> &array;
		int parts;

	public:
		void operator() (const tbb::blocked_range<int>& range) const;

		ParallelMatcher(MatchAbleString &mas, Pattern &p, std::vector<std::list<int>> &a, int parts) : mas(mas), p(p), array(a), parts(parts) {}
	};
};

#endif // MATCHABLESTRING_H_INCLUDED
