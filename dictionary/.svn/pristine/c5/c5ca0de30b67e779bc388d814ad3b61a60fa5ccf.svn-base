#include "dictionary.h"

template <class K, class V>
Dictionary<K, V>::Dictionary()
{
	curHeight = 1;
	maxHeight = 5;
	probability = .5;
	size=0;
	head = new SkipNode(maxHeight);
	tail = new SkipNode(maxHeight);
	for( int i = 1; i<=maxHeight;i++){
		head->fwdNodes[i] = tail;
	}
}

template <class K, class V>
Dictionary<K, V>::~Dictionary(){
	SkipNode* tmp;
	SkipNode* nxt;
	tmp = head;
	while(tmp!=NULL){
		nxt = tmp->fwdNodes[1];
		if(tmp!=NULL)
			delete tmp;
		tmp = nxt;
	}
}

template <class K, class V>
void Dictionary<K, V>::insert(const K & key, const V & value)
{
	int lvl = 0;
	int h = 0;
	SkipNode** updateVec = new SkipNode* [maxHeight+1];
	SkipNode* tmp = head;
	K cmpKey;

	for(h = curHeight; h>= 1; h--)
	{
		cmpKey = tmp->fwdNodes[h]->getKey();
		while ((cmpKey < key)&&(tmp->fwdNodes[h]!=tail))
		{
			tmp = tmp->fwdNodes[h];
			cmpKey = tmp->fwdNodes[h]->getKey();
		}
		updateVec[h] = tmp;
	}
	tmp = tmp->fwdNodes[1];
	cmpKey = tmp->getKey();

	if(cmpKey == key){
		delete [] updateVec;
		return;
	}
	size++;
	lvl = newLevel();
	if(lvl > curHeight){
		for(int i = curHeight+1;i<=lvl;i++)
			updateVec[i] = head;
		curHeight = lvl;
	}
	tmp = new SkipNode(key, value, lvl);
	for(int i = 1; i<= lvl; i++){
		tmp->fwdNodes[i] = updateVec[i]->fwdNodes[i];
		updateVec[i]->fwdNodes[i] = tmp;
	}
	delete [] updateVec;
}

template <class K, class V>
int Dictionary<K, V>::newLevel(){
	int tmpLvl = 1;
	while((random() < probability)&&(tmpLvl < maxHeight))
		tmpLvl++;

	return tmpLvl;
}

template <class K, class V>
void Dictionary<K, V>::remove(const K & key)
{
	SkipNode** updateVec = new SkipNode* [maxHeight+1];
	SkipNode* tmp = head;
	K cmpKey;

	for (int h = curHeight; h>0; h--){
		cmpKey = tmp->fwdNodes[h]->getKey();
		while((cmpKey < key)&&(tmp->fwdNodes[h]!=tail)){
			tmp = tmp->fwdNodes[h];
			cmpKey = tmp->fwdNodes[h]->getKey();
		}
		updateVec[h] = tmp;
	}
	tmp = tmp->fwdNodes[1];
	cmpKey = tmp->getKey();

	if((cmpKey==key)&&(tmp!=tail)){
		for(int i = 1; i<=curHeight; i++){
			if(updateVec[i]->fwdNodes[i] != tmp)
				break;
			updateVec[i]->fwdNodes[i] = tmp->fwdNodes[i];
		}
		delete tmp;
		size--;
		while((curHeight>1)&&((head->fwdNodes[curHeight]->getKey()==tail->getKey())))
			curHeight--;
		
	}
	delete[] updateVec;
}

template <class K, class V>
V Dictionary<K, V>::find(const K & key)
{
	int h=0;
	SkipNode** updateVec = new SkipNode*[maxHeight+1];
	SkipNode* tmp = head;
	K cmpKey;

	for(h = curHeight; h>=1; h--){
		if((tmp!=NULL)&&(tmp->fwdNodes!=NULL)&&(tmp->fwdNodes[h]!=NULL))
			cmpKey = tmp->fwdNodes[h]->getKey();
		while((cmpKey<key)&&tmp->fwdNodes[h]!=tail){
			tmp = tmp->fwdNodes[h];
			if(tmp->fwdNodes[h]!=NULL)
				cmpKey = tmp->fwdNodes[h]->getKey();
		}
		updateVec[h] = tmp;
	}
	tmp = tmp->fwdNodes[1];
	cmpKey = tmp->getKey();
	delete [] updateVec;
	if((cmpKey==key)&&(tmp!=tail))
		return tmp->getData();
	else
    	return V();
}

template <class K, class V>
bool Dictionary<K, V>::keyExists(const K & key)
{
	int h=0;
	SkipNode** updateVec = new SkipNode*[maxHeight+1];
	SkipNode* tmp = head;
	K cmpKey;

	for(h = curHeight; h>=1; h--){
		cmpKey = tmp->fwdNodes[h]->getKey();
		while(cmpKey<key){
			tmp = tmp->fwdNodes[h];
			cmpKey = tmp->fwdNodes[h]->getKey();
		}
		updateVec[h] = tmp;
	}
	tmp = tmp->fwdNodes[1];
	cmpKey = tmp->getKey();
	delete [] updateVec;
	if(cmpKey==key)
		return true;
	else
    	return false;
}

template <class K, class V>
bool Dictionary<K, V>::isEmpty() const
{
    return (size==0);
}

template <class K, class V>
Dictionary<K, V>::SkipNode::~SkipNode(){
	delete [] fwdNodes;
}

template <class K, class V>
Dictionary<K, V>::SkipNode::SkipNode(int h){
	height = h;
	key = K();
	data = V();
	fwdNodes = new SkipNode* [h+1];
	for(int x = 1; x <= height; x++){
		fwdNodes[x] = NULL;
	}
}

template <class K, class V>
Dictionary<K, V>::SkipNode::SkipNode(K k, V d, int h){
	height = h;
	key = k;
	data = d;
	fwdNodes = new SkipNode* [h+1];
	for(int x = 1; x<=height; x++)
		fwdNodes[x] = NULL;
}

template <class K, class V>
K Dictionary<K, V>::SkipNode::getKey(){
	return key;
}
template <class K, class V>
V Dictionary<K, V>::SkipNode::getData(){
	return data;
}
template <class K, class V>
int Dictionary<K, V>::SkipNode::getHeight(){
	return height;
}
