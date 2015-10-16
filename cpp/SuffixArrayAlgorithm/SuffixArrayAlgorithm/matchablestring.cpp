#include "matchablestring.h"

MatchAbleString::MatchAbleString(const char *orig) {
	length = (int)strlen(orig);

	original = new char[length + 1];
	strcpy_s(original, length + 1, orig);

	substringArray = new int[length];
	for (int i = 0; i < length; i++)
	{
		substringArray[i] = i;
	}

	isPreProcessed = false;
}

MatchAbleString::~MatchAbleString() {
	delete[] original;
	delete[] substringArray;
}

void MatchAbleString::preprocess(bool parallel) {
	auto comp = [this](int one, int other) {
		return strcmp(original + one, original + other) < 0;
	};

	if (!parallel) {
		std::sort(substringArray, substringArray + length, comp);
	}
	else {
		MergeSort<int>::parallelSort(substringArray, length, comp);
	}

	isPreProcessed = true;
}

int MatchAbleString::binarySearch(int min, int max, const std::unique_ptr<ComparerBase>& comparer) const {
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

std::vector<int> MatchAbleString::match(const char *pattern) const {
	if (!isPreProcessed) {
		throw std::runtime_error("This MatchAbleString hasn't been preprocessed yet!");
	}

	std::unique_ptr<ComparerBase> foc = std::make_unique<FirstOccurenceComparer>(original, pattern, substringArray, length);
	std::unique_ptr<ComparerBase> loc = std::make_unique<LastOccurenceComparer>(original, pattern, substringArray, length);

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

//void MatchAbleString::print() const {
//	for (size_t i = 0; i < length; i++) {
//		std::cout << original + substringArray[i] << std::endl;
//	}
//}