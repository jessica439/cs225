#include "dsets.h"
//addelements
//creates num unconnected root nodes
void DisjointSets::addelements(int n){
	for (int i = 0; i<n; i++){
		nodes.push_back(-1);
	}
}

//find
//finds the set that elem is in
int DisjointSets::find(int elem){
	if(nodes[elem] < 0)
		return elem;
	return find(nodes[elem]);
}

//unions the sets a and b
void DisjointSets::setunion(int a, int b){
	int setb = find(b);
	int seta = find(a);
	//no need to union, so stop doing stuff
	if(seta == setb)
		return;
	
	//need to union
	int sizeN = nodes[seta]+nodes[setb];
	if(nodes[seta]<=nodes[setb]){
		nodes[setb] = seta;
		nodes[seta] = sizeN;
	}else{
		nodes[seta] = setb;
		nodes[setb] = sizeN;
	}
	
}
