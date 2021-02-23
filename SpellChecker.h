#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H
#include <string>
using namespace std;
const int MAX = 6;
namespace sdds {
	class SpellChecker {
		string m_badWords[MAX];
		string m_goodWords[MAX];
		int CNT[MAX]{0};
	public:
		SpellChecker(const char* filename);
		void operator()(string& text);
	};
}
#endif