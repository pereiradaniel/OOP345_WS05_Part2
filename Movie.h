#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H
#include <string>
#include "SpellChecker.h"
using namespace std;
namespace sdds {
	class Movie {
		string m_title{};
		size_t m_year{};
		string m_des{};
	public:
		Movie() = default;
		const string& title() const;
		Movie(const string& strMovie);
		template <typename T>
			void fixSpelling(T& spellChecker) {
				spellChecker(m_title);
				spellChecker(m_des);
			}
		friend ostream& operator<<(ostream& os, const Movie& src);
	};
}
#endif
