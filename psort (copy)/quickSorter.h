#ifndef QUICKSORTER_H
#define QUICKSORTER_H

#include "sorter.h"

class quickSorter : public sorter{
	public:
		quickSorter() {};
	
		template <class T>
		virtual void sort(vector<T>* array);
}
#endif
