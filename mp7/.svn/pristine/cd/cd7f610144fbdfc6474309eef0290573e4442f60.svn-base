#ifndef DSETS_H 
#define DSETS_H
#include <vector>

using namespace std;

class DisjointSets
{
	public:
		//adds elements
		void addelements(int num);
		//compresses paths and returns the index of the root of the up-tree
		// in which the parameter element resides
		int find(int elem);
		//sets the union
		void setunion(int a, int b);
	private:
		//the uptree
		vector<int> nodes;
};
#endif //DSETS_H
