#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>

#include "matchablestring.h"

//int main() {
//	std::string s = "i had to, Hence, i peed the fence. i don't see the adHence";
//	std::string pat = "ence";
//
//	MatchAbleString str(s);
//    Pattern p(pat);
//    p.preprocess();
//
//	auto l = str.match(p, true);
//	for (const auto& p : *l) {
//		std::cout << p << " : '" << s.substr(p, pat.length()) << "'" << std::endl;
//	}
//
//	char c;
//	std::cin >> c;
//
//    return 0;
//}

int measure(std::string orig, std::string pat, bool parallel, int num) {
	long int start;
	int elapsed = 0;
	std::unique_ptr<std::vector<int>> l;

	MatchAbleString str(orig);

	for (int i = 0; i < 5 * num; i++) {
		Pattern p(pat);

		start = GetTickCount();
		p.preprocess();
		l = str.match(p, parallel);
		elapsed += GetTickCount() - start;
	}

	/*std::cout << (parallel ? "Parallel" : "Single thread") << " matching took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms" << std::endl;
	std::cout << "Found " << l->size() << " matches." << std::endl;*/

	return elapsed / 5;
}

int main(int argc, char **argv) {

#if defined _M_IX86
	std::string path = "..\\..\\..\\resources\\";
#elif defined _M_X64
	std::string path = "..\\..\\..\\..\\resources\\";
#endif

	path += argv[1];

	std::ifstream t;
	t.open(path, std::ifstream::binary);      // open input file
	t.seekg(0, t.end);    // go to the end
	int length = t.tellg();           // report location (this is the length)

	//std::cout << length << std::endl;

	t.seekg(0, t.beg);    // go back to the beginning
	char *buffer = new char[length + 1];    // allocate memory for a buffer of appropriate dimension
	t.read(buffer, length);       // read the whole file into the buffer
	buffer[length] = '\0';
	t.close();                    // close file handle

	size_t tmp = (length + 1) * 64 + 1;
	char *orig = new char[tmp];
	orig[0] = '\0';
	for (int i = 0; i < 64; i++) {
		strcat_s(orig, tmp, buffer);
	}

	delete[] buffer;

	std::cout << strlen(orig) << ";";

	/*int num = atoi(argv[3]);
	std::cout << num << ";";*/

	std::cout << measure(orig, argv[2], false, 1000) << ";";
	std::cout << measure(orig, argv[2], true, 1000) << std::endl;

	delete[] orig;

	return 0;
}
