#ifndef MATCHABLESTRING_H
#define MATCHABLESTRING_H

#include <cstring>
#include <vector>

#include "pattern.h"

class MatchableString {
protected:
	char *str;
	int length;

public:
	MatchableString(const char *c);
	virtual ~MatchableString();

	virtual void preprocess(bool parallel) {}
	virtual std::vector<int> match(Pattern &p, bool parallel) const = 0;
};

#endif