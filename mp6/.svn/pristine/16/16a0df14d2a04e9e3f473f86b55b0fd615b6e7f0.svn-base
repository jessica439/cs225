/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <iostream>
using namespace std;

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    if (first[curDim] == second[curDim])
        return (second > first);
    return (second[curDim] > first[curDim]);
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    int potDistance = findDistance(target, potential);
    int currDistance = findDistance(target, currentBest);
    
    
    if (potDistance < currDistance)
    	return true;
    if (potDistance == currDistance)
    	return (potential < currentBest);
    return false;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    points = newPoints;
    helper(points, 0, (int) (points.size() - 1), 0);
}

template<int Dim>
void KDTree<Dim>::helper(vector< Point<Dim> > & newPoints, int left, int right, int dimen)
{
    if (left > right) return;
	
    //quick select @ median
	int mid = (left+right) / 2;
	points[mid] = select(newPoints, left, right, mid, dimen);
	
    //recurse through left and right partitions
	helper(newPoints, left, mid - 1,  (dimen + 1) % Dim);
    helper(newPoints, mid + 1, right, (dimen + 1) % Dim);
}

template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & list, int left, int right, int pivotIndex, int dimen)
{
	Point<Dim> pivotValue = list[pivotIndex];
	swap(list[pivotIndex], list[right]); // Move pivot to end
	int storeIndex = left;
	int i = left;
	while(i<right)
	//for (int i = left; i < right; i++)
	{
		if (smallerDimVal(list[i], pivotValue, dimen))
		{
            swap(list[i], list[storeIndex]);
			storeIndex++;
		}
		i++;
	}
	swap(list[right], list[storeIndex]); // Move Pivot to its final place
	return storeIndex;
}

template<int Dim>
Point<Dim> KDTree<Dim>::select(vector< Point<Dim> > & list, int left, int right, int k, int dimen)
{
	while(left < right) // loop
	{
		int pivotNewIndex = partition(list, left, right, (right + left) / 2, dimen);
		
        if (pivotNewIndex == k)
			return list[pivotNewIndex];

		else if (k <  pivotNewIndex)
			right = pivotNewIndex - 1; // search left of pivotNewIndex
		
        else
			left = pivotNewIndex + 1; // search right of pivotNewIndex
	}
	return list[left];
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
   return findNearestNeighbor(0, points.size() - 1, query, 0);
}

template<int Dim>
int KDTree<Dim>::findDistance(const Point<Dim> p1, const Point<Dim> p2) const
{
    //don't need the square root, just return sum of squares
    int sum = 0, total = 0;
    for (int x = 0; x < Dim; ++x)
    {
        sum = p1[x] - p2[x];
        total += sum * sum;
    }
    return total;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(int begin, int end, const Point<Dim> & query, int curDim) const
{
	int mid = (begin + end) / 2;

    if (begin >= end) return points[begin];
	
	Point<Dim> currBest, temp;
	
    //root is less than query, search right
    if (smallerDimVal(points[mid], query, curDim))
		currBest = findNearestNeighbor(mid + 1, end, query, (curDim + 1) % Dim);
	
    else // root is greater than query, search left 
		currBest = findNearestNeighbor(begin, mid - 1, query, (curDim + 1) % Dim);

    //check if root is closer than subtrees, set to currbest
    if (shouldReplace(query, currBest, points[mid]))
        currBest = points[mid];
	
    //back traversal to check outside hyperrectangle
    //find the distance of currBest
    int radius = findDistance(query, currBest);
	
    //get splitting plane distance, not euclidean distance
    int distance = (-points[mid][curDim]+query[curDim])*(query[curDim] - points[mid][curDim]);
	//int distance = findDistance(query, points[mid]);
    //if splitting plane is closer than current best distance
    if (distance <= radius)
	{
		// search through the opposite side of the tree as before
        if (smallerDimVal(points[mid], query, curDim))
			temp = findNearestNeighbor(begin, mid - 1, query, (curDim + 1) % Dim);
	    else
			temp = findNearestNeighbor(mid + 1, end, query, (curDim + 1) % Dim);
		//test if temp candidate is closer than currBest
        if (shouldReplace(query, currBest, temp))
			currBest = temp;
	}
	
	return currBest;
}

