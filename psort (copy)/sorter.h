#ifndef SORTER_H
#define SORTER_H

#include <vector>

class sorter {
	public:
		
		virtual ~sorter() {};
		
		template <class T>
		virtual void sort(vector<T>* array) = 0;
};
#endif
