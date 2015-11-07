#ifndef MATCHABLESTRINGB_H
#define MATCHABLESTRINGB_H

#include <list>
#include <vector>

#include "tbb\blocked_range.h"
#include "tbb\parallel_for.h"

#include "..\matchablestring.h"
#include "..\pattern.h"

class MatchableStringB : public MatchableString {
    static int findFirst(const Pattern &p, const char *str, size_t length);
	static std::vector<int>* matchSubstr(const Pattern &p, const char *str_, int length_, int startPos);

	std::vector<int>* matchSubstr(const Pattern &p, int parts, int i) const;

public:
	MatchableStringB(const char *c) : MatchableString(c) {}
	virtual ~MatchableStringB() {}

	MatchableStringB(const MatchableStringB&) = delete;
	MatchableStringB& operator=(const MatchableStringB&) = delete;

	virtual std::vector<int> match(Pattern &p, bool parallel) const override;
};

#endif // MATCHABLESTRINGB_H
