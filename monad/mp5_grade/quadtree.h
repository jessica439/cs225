// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"
#include "math.h"

class Quadtree
{
	public:
	
    Quadtree();
    Quadtree(const PNG & source, int resolution);
    Quadtree(Quadtree const & other);
    ~Quadtree();
    Quadtree const & operator=(Quadtree const & other);
    void buildTree(PNG const & source, int resolution);
    RGBAPixel getPixel(int x, int y) const;
    PNG decompress() const;
    void clockwiseRotate();
    void prune(int tolerance);
    int pruneSize(int tolerance) const;
    int idealPrune (int numLeaves) const;
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	
	
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"

    //the dimensions of the current img represented by the quadtree
    int imgsize;

    //recursive helper, frees all dynamic memory from root ptr
    void deleteTree(QuadtreeNode * ptr) const;

    //recursive helper, copies quadtree to new quadtree
    Quadtree::QuadtreeNode * copyTree(const Quadtree::QuadtreeNode * ptr) const;

    //recursive buildHelper function
    //builds the quadtree of the source image
    //given integers are the coords of the left corner of squares of length d
    //to build the tree of 
    //returns the root of the built tree
    QuadtreeNode * buildHelper(const PNG & source, int x, int y, int d) const;

    //recursive getHelper function
    //gets the pixel located at x, y of a tree at given root
    //upper left corner of given ptr is (x*d, y*d) where d is the side length
    //of the square represented by given ptr
    //returns the pixel or the average of the square wehre the pixel used to be
    RGBAPixel getHelper(QuadtreeNode * ptr, int x, int y, int dx, int dy, int d) const;

    //recursive decompHelper function
    //decompresses the tree rooted at teh given pointer
    //(x,y) is the top left corner of the square of size d represented by ptr
    void decompHelper(QuadtreeNode * ptr, PNG & img, int x, int y, int d) const;
    bool isPrunable(QuadtreeNode * temp, int tolerance, QuadtreeNode * avg) const;
    void clockwiseHelper(QuadtreeNode * temp) const;
    void pruneHelper(QuadtreeNode * temp, int tolerance) const;
    int difference(RGBAPixel px1, RGBAPixel px2) const;
    int pruneSizeHelper(QuadtreeNode * input, int tolerance) const;

};

#endif
