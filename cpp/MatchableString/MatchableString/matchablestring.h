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

	/**
	 * Preprocesses the main text, has to be called before the first matching.
	 * @param parallel Sets whether to run parallel or not
	 */
	virtual void preprocess(bool parallel) {}

	/**
	 * Matches the given pattern on the string.
	 * @param pattern The pattern to match
	 * @param parallel Sets whether to run parallel or not
	 * @return The list of the occurrences
	 */
	virtual std::vector<int> match(Pattern &p, bool parallel) const = 0;
};

#endif