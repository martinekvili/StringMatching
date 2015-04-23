#include <iostream>
#include <fstream>
#include <windows.h>

#include "matchablestring.h"

int main2()
{
    Pattern p("Hence");
    p.preprocess();
    for (int c = 0; c < 256; c++) {
        if (p.getDelta1(c) != p.getLength()) {
            std::cout << (char)c << " (" << c << ") : " << p.getDelta1(c) << std::endl;
        }
    }
    std::cout << std::endl;
   /* for (size_t i = 0; i < p.getLength(); i++) {
        std::cout << p.getDelta2(i) << ' ';
    }
    std::cout << std::endl;

    Pattern p("AT");
    const char *c = "WHICH FINALLY HALTS.  AT THAT POINT";
    MatchAbleString s(c);

    std::list<int> m = s.match(p);
    for (typename std::list<int>::iterator p = m.begin(); p != m.end(); p++) {
        std::cout << *p << " : '" << c + *p << "'" << std::endl;
    }*/

    return 0;
}

int measure(const char *orig, const char *pat, bool parallel) {
	long int start;
	int elapsed = 0;

	for (int i = 0; i < 100; i++) {
		MatchAbleString str(orig);
		Pattern p(pat);

		start = GetTickCount();
		p.preprocess();
		std::list<int> l = str.match(p);
		elapsed += GetTickCount() - start;

		//std::cout << "Matching took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms" << std::endl;
		//std::cout << "Found " << l.size() << " occurrences." << std::endl;
		/*char *szo = new char[strlen(pat) + 1];
		strncpy(szo, orig + l.front(), strlen(pat));
		std::cout << l.front() << ": " << szo << "\n" <<std::endl;
		delete[] szo;*/
	}

	return elapsed;
}

int main(int argc, char **argv)
{
	std::ifstream t;
	int length;
	t.open("bfranklin.txt", std::ofstream::in);      // open input file
	t.seekg(0, std::ios::end);    // go to the end
	length = t.tellg();           // report location (this is the length)
	t.seekg(0, std::ios::beg);    // go back to the beginning
	char *buffer = new char[length];    // allocate memory for a buffer of appropriate dimension
	t.read(buffer, length);       // read the whole file into the buffer
	t.close();                    // close file handle


    //const char *buffer = "i had to, Hence, i peed the fence. i don't see the adHence";

	char *orig = new char[strlen(buffer) * 32 + 1];
	orig[0] = '\0';
	for (int i = 0; i < 32; i++) {
		strcat(orig, buffer);
	}

	std::cout << strlen(orig) << std::endl;

	delete[] buffer;

	std::cout << measure(orig, "contiguity", false) /*<< ";" << measure(orig, true)*/ << std::endl;

	delete[] orig;

	return 0;
}
