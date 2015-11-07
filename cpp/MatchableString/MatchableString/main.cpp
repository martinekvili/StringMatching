#include <iostream>
#include <memory>
#include <string>

#include "matchablestring.h"
#include "pattern.h"
#include "boyer\matchablestringb.h"
#include "suffixarray\matchablestringsa.h"

void measureSimple() {
	std::string  orig = "i had to, Hence, i peed the fence. i don't see the adHence";
	std::unique_ptr<MatchableString> sm = std::make_unique<MatchableStringSA>(orig.data());
	sm->preprocess(false);

	std::string pat = "ence";
	Pattern p(pat.data());
	std::vector<int> h = sm->match(p, false);

	for (auto i : h) {
		std::cout << i << " : " << orig.substr(i, pat.length()) << std::endl;
	}

	char c;
	std::cin >> c;
}

int main(int argc, char **argv)
{
	measureSimple();

	return 0;
}