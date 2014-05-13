/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary tree
 *  is just the length of the longest path from the root to a leaf, and that the
 *  height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
	// Call recursive helper function on root
	return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node * subRoot) const
{
	// Base case
	if (subRoot == NULL)
        return -1;
	
	// Recursive definition
	return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that node
 *  itself, and everything to the right of a node will be printed out after that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
	// Call recursive helper function on the root
	printLeftToRight(root);

	// Finish the line
	cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
	// Base case - null node
	if (subRoot == NULL)
		return;

	// Print left subtree
	printLeftToRight(subRoot->left);

	// Print this node
	cout << subRoot->elem << ' ';

	// Print right subtree
	printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
	mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node * subRoot){
	if(subRoot->right == NULL&&subRoot->left==NULL){
		return;
	}
	if(subRoot->right != NULL)
		mirror(subRoot->right);
	if(subRoot->left != NULL)
		mirror(subRoot->left);
	Node * temp = subRoot->right;
	subRoot->right = subRoot->left;
	subRoot->left = temp;
}


/**
 * @return True if an in-order traversal of the tree would produce a nondecreasing list
 *  output values, and false otherwise. This is also the criterion for a binary tree to be
 *  a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
	bool ret = true;
	T a,b;
	vector<T> V;

	isOrdered(root,V);

	if (V.size() < 2)
		return true;

	a=V.back();
	V.pop_back();

	while(!V.empty()){
		b=V.back();
		V.pop_back();
		if(a<b)
			ret=false;
		a=b;
	}
	return ret;
}

template <typename T>
void BinaryTree<T>::isOrdered(const Node * subRoot, vector<T> & V)const{
/*	if(subRoot->right == NULL||subRoot->left==NULL)
		return true;
	//Node * temp = isOrdered(subroot->left);
	//Node * temp2 = isOrdered(subroot->right);
	if(subRoot->left->elem>subRoot->right->elem)
		return false;
	else if(subRoot->left->elem>subRoot->elem)
		return false;
	else if(subRoot->elem>subRoot->right->elem)
		return false;
	else
		return isOrdered(subRoot->right)&&isOrdered(subRoot->left);
	static Node* prev = NULL;
	if(subRoot){
		if(!isOrdered(subRoot->left))
			return false;
		if(prev != NULL && subRoot->elem <= prev->elem)
			return false;

		prev = root;

		return isOrdered(subRoot->right);
	}
	return true;
	*/
	if(subRoot == NULL)
		return;

	isOrdered(subRoot->left,V);
	V.push_back(subRoot->elem);
	isOrdered(subRoot->right,V);

}
/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards, ending at a
 *  leaf node. Paths ending in a left node should be printed before paths ending in a node
 *  further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
	vector<T> temp;
	printPaths(root, temp);
}

template <typename T>
void BinaryTree<T>::printPaths(const Node * subRoot, vector<T> & temp)const
{
	if(!subRoot)
		return;
	temp.push_back(subRoot->elem);
	if((!subRoot->left)&&(!subRoot->right))
		printl(temp);

	printPaths(subRoot->left,temp);
	printPaths(subRoot->right,temp);

	temp.pop_back();
}

template <typename T>
void BinaryTree<T>::printl(vector<T> temp) const
{
	vector<T> a;
	while (!temp.empty())
	{
		a.push_back(temp.back());
		temp.pop_back();
	}

	cout << "Path:";

	while(!a.empty())
	{
		cout<< ' '<<a.back();
		a.pop_back();
	}

	cout << endl;
	return;
}

/**
 * Each node in a tree has a distance from the root node - the depth of that node,
 *  or the number of edges along the path from that node to the root. This function returns
 *  the sum of the distances of all nodes to the root node (the sum of the depths of all
 *  the nodes). Your solution should take O(n) time, where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
	int num = 0;
    sumDistances(root, num, 0);
    return num;
}

template <typename T>
void BinaryTree<T>::sumDistances(const Node * subRoot, int & temp,int num)const
{
	if(subRoot==NULL)
		return;
	temp +=num;
	sumDistances(subRoot->left,temp, num+1);
	sumDistances(subRoot->right, temp, num+1);

}
