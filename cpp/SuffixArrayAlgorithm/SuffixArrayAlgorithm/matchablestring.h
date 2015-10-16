#ifndef MATCHABLESTRING_H
#define MATCHABLESTRING_H

#include <algorithm>
#include <vector>
#include <memory>

#include "comparers.h"
#include "mergesort.hpp"

class MatchAbleString
{
private:
	char *original;
	int *substringArray;
	int length;
	bool isPreProcessed;

	int binarySearch(int min, int max, const std::unique_ptr<ComparerBase>& comparer) const;

public:
	MatchAbleString(const char *orig);
	~MatchAbleString();

	MatchAbleString(const MatchAbleString &) = delete;
	MatchAbleString& operator= (const MatchAbleString &) = delete;

	void preprocess(bool parallel = false);

	std::vector<int> match(const char *pattern) const;
	
	//void print() const;
};

#endif // MATCHABLESTRING_H