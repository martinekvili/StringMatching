#ifndef MATCHABLESTRINGSA_H
#define MATCHABLESTRINGSA_H

#include <algorithm>
#include <vector>
#include <memory>

#include "comparers.h"
#include "mergesort.hpp"
#include "..\matchablestring.h"
#include "..\pattern.h"

class MatchableStringSA : public MatchableString {
private:
	int *substringArray;
	bool isPreProcessed;

	int binarySearch(int min, int max, const std::unique_ptr<ComparerBase>& comparer) const;

public:
	MatchableStringSA(const char *orig);
	virtual ~MatchableStringSA();

	MatchableStringSA(const MatchableStringSA &) = delete;
	MatchableStringSA& operator= (const MatchableStringSA &) = delete;

	virtual void preprocess(bool parallel) override;

	std::vector<int> match(Pattern& pattern, bool parallel) const override;
};

#endif // MATCHABLESTRINGSA_H