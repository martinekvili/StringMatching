#ifndef MATCHABLESTRINGS_H
#define MATCHABLESTRINGS_H

#include <memory>
#include <string>

#include "matchablestring.h"
#include "boyer\matchablestringb.h"
#include "suffixarray\matchablestringsa.h"

class MatchableStrings {
public:

	/**
	 * Choices for the approximate number of matches.
	 */
	static enum NumberOfMatches {

		/**
		 * This object will be used for less than 1000 matches.
		 */
		LessThan1000,

		/**
		 * This object will be used for more than 1000 matches.
		 */
		MoreThan1000
	};

	/**
	 * Creates a matchable string object using Boyer-Moore algorithm.
	 * @param s The main text to match patterns on
	 * @return A matchable string object
	 */
	static std::unique_ptr<MatchableString> createBoyer(const char *s);

	/**
	 * Creates a matchable string object using Suffix Array algorithm.
	 * @param s The main text to match patterns on
	 * @return A matchable string object
	 */
	static std::unique_ptr<MatchableString> createSuffixArray(const char *s);

	/**
	 * Creates a matchable string object with a suitable implementation.
	 * @param s The main text to match patterns on
	 * @param approx The approximate number of uses
	 * @return A matchable string object
	 */
	static std::unique_ptr<MatchableString> create(const char *s, NumberOfMatches approx);
};

#endif