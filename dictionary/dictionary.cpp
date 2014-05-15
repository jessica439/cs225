//Advanced Dictionary Structure for Spring 2014 CS225 Honors Section
//Implemented with a SkipList of maximum height 5 and height probability .25
//Kevin Scheer

#include "dictionary.h"

//default skiplist constructor
template <class K, class V>
Dictionary<K, V>::Dictionary()
{
	curHeight = 1;
	maxHeight = 5; //arbitrarily chosen maxheight
	probability = .5; //arbitrarily chosen probability
	size=0;
	head = new SkipNode(maxHeight);
	tail = new SkipNode(maxHeight);
	for( int i = 1; i<=maxHeight;i++){
		head->fwdNodes[i] = tail; //since there are only the head and tail
	}							  //nodes, the node after the head for every
}								  //height is the tail

//destructor for the whole list
template <class K, class V>
Dictionary<K, V>::~Dictionary(){
	SkipNode* tmp;
	SkipNode* nxt;
	tmp = head;
	while(tmp!=NULL){ //loop through until it hits the tail
		nxt = tmp->fwdNodes[1]; //stores the next node pointer for safe keeping
		if(tmp!=NULL)
			delete tmp; //deletes current node
		tmp = nxt;		//moves on to the next node
	}
}

//inserts data into list with given key
template <class K, class V>
void Dictionary<K, V>::insert(const K & key, const V & value)
{
	int lvl = 0;
	int h = 0;
	SkipNode** updateVec = new SkipNode* [maxHeight+1];
	SkipNode* tmp = head;
	K cmpKey;//initialize current key

	for(h = curHeight; h>= 1; h--)// loops through every level in use
	{
		cmpKey = tmp->fwdNodes[h]->getKey();//gets first key in current height
		while ((cmpKey < key)&&(tmp->fwdNodes[h]!=tail))
		{
			tmp = tmp->fwdNodes[h];				//if current key is less than key to be inserted, check next node
			cmpKey = tmp->fwdNodes[h]->getKey();//update current key
		}
		updateVec[h] = tmp;
	}
	tmp = tmp->fwdNodes[1];
	cmpKey = tmp->getKey();

	if(cmpKey == key){//if key already exists, don't insert it
		delete [] updateVec;
		return;
	}//else
	size++;//increment size
	lvl = newLevel(); //pick level for new node
	if(lvl > curHeight){ //if new level is larger than current largest level, set up list for higher levels
		for(int i = curHeight+1;i<=lvl;i++)
			updateVec[i] = head;
		curHeight = lvl;
	}
	tmp = new SkipNode(key, value, lvl); //create new node with key, value, and selected level
	for(int i = 1; i<= lvl; i++){
		tmp->fwdNodes[i] = updateVec[i]->fwdNodes[i];
		updateVec[i]->fwdNodes[i] = tmp;
	}
	delete [] updateVec;
}

//returns a random level based on the probability and maxheight
template <class K, class V>
int Dictionary<K, V>::newLevel(){
	int tmpLvl = 1;
	while((random() < probability)&&(tmpLvl < maxHeight))
		tmpLvl++;

	return tmpLvl;
}

//removes node of given key
template <class K, class V>
void Dictionary<K, V>::remove(const K & key)
{
	SkipNode** updateVec = new SkipNode* [maxHeight+1];
	SkipNode* tmp = head;
	K cmpKey;
	//level search function from earlier to find node with given key
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
	//if key is what we're looking for, remove it from list, otherwise do nothing
	if((cmpKey==key)&&(tmp!=tail)){
		for(int i = 1; i<=curHeight; i++){
			if(updateVec[i]->fwdNodes[i] != tmp)
				break;
			updateVec[i]->fwdNodes[i] = tmp->fwdNodes[i];
		}
		delete tmp;
		size--;//decrement size
		while((curHeight>1)&&((head->fwdNodes[curHeight]->getKey()==tail->getKey())))
			curHeight--;
		
	}
	delete[] updateVec;
}

//returns data of given key
template <class K, class V>
V Dictionary<K, V>::find(const K & key)
{
	int h=0;
	SkipNode** updateVec = new SkipNode*[maxHeight+1];
	SkipNode* tmp = head;
	K cmpKey;
	//search for key like in earlier functions
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
		return tmp->getData();//return data at key location given
	else
    	return V();
}

//returns true if given key exists in the list
template <class K, class V>
bool Dictionary<K, V>::keyExists(const K & key)
{
	int h=0;
	SkipNode** updateVec = new SkipNode*[maxHeight+1];
	SkipNode* tmp = head;
	K cmpKey;
	//search function from earlier functions
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
	if(cmpKey==key)//same as find, but return boolean rather than the applicable data
		return true;
	else
    	return false;
}

//tests if skiplist is empty
template <class K, class V>
bool Dictionary<K, V>::isEmpty() const
{
    return (size==0);//returns 1 if list is empty
}

//destructor
template <class K, class V>
Dictionary<K, V>::SkipNode::~SkipNode(){
	delete [] fwdNodes;//deletes the forward node pointer array
}

//creates a default skip node at height h
template <class K, class V>
Dictionary<K, V>::SkipNode::SkipNode(int h){
	height = h;
	key = K();//default key object
	data = V();//default data object
	fwdNodes = new SkipNode* [h+1];
	for(int x = 1; x <= height; x++){
		fwdNodes[x] = NULL;//sets all forward node pointers to null
	}
}

//creates a node with given key data and height
template <class K, class V>
Dictionary<K, V>::SkipNode::SkipNode(K k, V d, int h){
	height = h;//sets internal variables to given values
	key = k;
	data = d;
	fwdNodes = new SkipNode* [h+1];
	for(int x = 1; x<=height; x++)
		fwdNodes[x] = NULL;//sets all forward node pointers to NULL (have to be set manually)
}

//returns key of node
template <class K, class V>
K Dictionary<K, V>::SkipNode::getKey(){
	return key;
}

//returns data of node
template <class K, class V>
V Dictionary<K, V>::SkipNode::getData(){
	return data;
}

//returns height of node
template <class K, class V>
int Dictionary<K, V>::SkipNode::getHeight(){
	return height;
}
