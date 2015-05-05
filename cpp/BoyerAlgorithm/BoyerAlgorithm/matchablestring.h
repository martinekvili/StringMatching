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

    static int findFirst(const Pattern &p, const char *str, size_t length);
	static std::vector<int>* matchSubstr(const Pattern &p, const char *str_, int length_, int startPos);

	std::vector<int>* matchSubstr(const Pattern &p, int parts, int i);

public:
    MatchAbleString(const char *c);
    ~MatchAbleString();

	std::vector<int> match(const Pattern &p, bool parallel = false);

	class ParallelMatcher {
		MatchAbleString &mas;
		const Pattern &p;
		std::vector<std::vector<int>*> &array;
		int parts;

	public:
		void operator() (const tbb::blocked_range<int>& range) const;

		ParallelMatcher(MatchAbleString &mas, const Pattern &p, std::vector<std::vector<int>*> &a, int parts) : mas(mas), p(p), array(a), parts(parts) {}
	};
};

#endif // MATCHABLESTRING_H_INCLUDED
