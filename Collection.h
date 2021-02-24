#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <string>
using namespace std;
namespace sdds {
	template <typename T>
	class Collection {
		string c_name;
		T* c_item{};
		size_t c_cnt{};
		void (*c_observer)(const Collection<T>&, const T&) { nullptr };
	public:
		Collection(const string& name) {
			c_name = name;
			c_item = nullptr;
			c_cnt = 0;
			c_observer = nullptr;
		}
		~Collection() {
			delete[] c_item;
			c_item = nullptr;
		}
		Collection(Collection&) = delete;
		Collection& operator=(Collection&) = delete;
		const string& name() const {
			return c_name;
		}
		size_t size() const {
			return c_cnt;
		}
		void setObserver(void (*observer)(const Collection<T>&, const T&)) {
			c_observer = observer;
		}
		Collection<T>& operator+=(const T& item) {
			bool exists = false;

			for (size_t i = 0; i < c_cnt; ++i) {
				if (c_item[i].title() == item.title()) {
					exists = true;
				}
			}
			if (!exists) {
				if (c_cnt == 0) {
					c_cnt++;
					c_item = new T[c_cnt];
					c_item[0] = item;
				}
				else {
					T* temp = new T[c_cnt];
					for (size_t i = 0; i < c_cnt; ++i) {
						temp[i] = c_item[i];
					}
					delete[] c_item;
					c_cnt++;
					c_item = new T[c_cnt];
					for (size_t j = 0; j < c_cnt - 1; ++j) {
						c_item[j] = temp[j];
					}
					delete[] temp;
					c_item[c_cnt - 1] = item;
					if (c_observer != nullptr) {
						c_observer(*this, item);
					}
				}
			}
			return *this;
		}
		T& operator[](size_t idx) const {
			if (idx >= c_cnt || idx < 0) {
				throw out_of_range("Bad index [" + to_string(idx) + "]. " + "Collection has [" + to_string(c_cnt) + "] items.");
			}
			else {
				return c_item[idx];
			}
		}
		T* operator[](string title) const {
			int idx = -1;
			for (size_t i = 0; i < c_cnt; i++) {
				if (c_item[i].title() == title) {
					idx = i;
				}
			}
			if (idx == -1) {
				return nullptr;
			}
			else {
				return &c_item[idx];
			}
		}

		friend ostream& operator<<(ostream& os, Collection& src) {
			for (size_t i = 0; i < src.size(); ++i) { // d
				os << src.c_item[i];
			}
			return os;
		}
	};
}
#endif