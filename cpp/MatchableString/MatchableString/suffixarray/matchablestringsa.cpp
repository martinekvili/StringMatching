#include "matchablestringsa.h"

MatchableStringSA::MatchableStringSA(const char *orig) : MatchableString(orig) {
	substringArray = new int[length];
	for (int i = 0; i < length; i++)
	{
		substringArray[i] = i;
	}

	isPreProcessed = false;
}

MatchableStringSA::~MatchableStringSA() {
	delete[] substringArray;
}

void MatchableStringSA::preprocess(bool parallel) {
	auto comp = [this](int one, int other) {
		return strcmp(str + one, str + other) < 0;
	};

	if (!parallel) {
		std::sort(substringArray, substringArray + length, comp);
	}
	else {
		MergeSort<int>::parallelSort(substringArray, length, comp);
	}

	isPreProcessed = true;
}

int MatchableStringSA::binarySearch(int min, int max, const std::unique_ptr<ComparerBase>& comparer) const {
	if (min == max) {
		return -1;
	}

	int num = (min + max) / 2;

	switch (comparer->compare(num)) {
	case 0:
		return num;
	case -1:
		return binarySearch(num + 1, max, comparer);
	case 1:
		return binarySearch(min, num, comparer);
	default:
		throw std::logic_error("Not possible to get here - theoretically.");
	}
}

std::vector<int> MatchableStringSA::match(Pattern& pattern, bool parallel) const {
	if (!isPreProcessed) {
		throw std::runtime_error("This MatchAbleString hasn't been preprocessed yet!");
	}

	std::unique_ptr<ComparerBase> foc = std::make_unique<FirstOccurenceComparer>(str, pattern.getString(), substringArray, length);
	std::unique_ptr<ComparerBase> loc = std::make_unique<LastOccurenceComparer>(str, pattern.getString(), substringArray, length);

	int first = binarySearch(0, length, foc);
	int last = binarySearch(0, length, loc);

	if (first == -1)
	{
		return std::vector<int>();
	}
	else
	{
		std::vector<int> tmp;

		for (int i = first; i <= last; i++) {
			tmp.push_back(substringArray[i]);
		}

		std::sort(tmp.begin(), tmp.end());

		return tmp;
	}
}