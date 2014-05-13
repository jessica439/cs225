// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"

using namespace std;

// the no argument constructor, produces empty quadtree

Quadtree::Quadtree()
{
    root = NULL;
    imgsize = 0;
}


//the two argument constructor, produces a quadtree of the upper left
//d by d block of the given source image
//
//inputs : PNG object with dimensions larger than d
//          , integer d which is a power of two
//
Quadtree::Quadtree(const PNG & source, int resolution)
{    
    root = NULL;
    imgsize = resolution;
    buildTree(source,resolution);
}

//the copy constructor
//
//sets the quadtree to be a copy of the given argument
//
//inputs : quadtree object to be copied
//
Quadtree::Quadtree(Quadtree const & other)
{
    imgsize = other.imgsize;
    
    //recursive helper function necessary (copyTree)
    root = copyTree(other.root);
}

//destructor, frees all memory associated with quadtree
//
Quadtree::~Quadtree()
{
    //recurive helper function necessary (deleteTree)
    deleteTree(root);
    root = NULL;
}

//deleteTree recursive helper function
//
//frees all dynamic memory used by the tree with the root at teh given pointer
//
//inputs : QuadtreeNode * to root
void Quadtree::deleteTree(Quadtree::QuadtreeNode * ptr) const
{
	//basecase
	//cout << "begin" << endl;
	if (ptr == NULL)
		return;

	//recursive cases
	deleteTree(ptr->neChild);
	deleteTree(ptr->nwChild);
	deleteTree(ptr->seChild);
	deleteTree(ptr->swChild);

	delete ptr;

}

//assignment operator
//
//frees memory associated with this quadtree and sets its contents to be
//equal to the parameters
//
//inputs : the other quadtree to be copied
//
//outputs : a const reference to the quadtree value that was copied
//
Quadtree const & Quadtree::operator=(Quadtree const & other)
{
    //free the space used by the original tree 
    //recursive helper fxn necessary (deleteTree)
    deleteTree(root);
	


    //recursive helper function necessary (copyTree)
    root = copyTree(other.root);

    imgsize = other.imgsize;

    return *this;
}

//copyTree helper function
//
//makes a copy of the tree with the given root pointer
//
//inputs : pointer to root of quadtree
//
//outputs : pointer to root of copied quadtree
Quadtree::QuadtreeNode * Quadtree::copyTree(const Quadtree::QuadtreeNode * ptr) const
{
	
    //basecase
    if (ptr == NULL)
    	return NULL;
   	
   	//recursive copying
   	else{
   	QuadtreeNode * ret = new QuadtreeNode;
   	ret->element = ptr->element;
    ret->seChild = copyTree(ptr->seChild);
    ret->neChild = copyTree(ptr->neChild);
    ret->swChild = copyTree(ptr->swChild);
    ret->nwChild = copyTree(ptr->nwChild);

    return ret;
    }
    
    
}

//buildtree function
//
//deletes the current contents of the quadtree object,
//then turns it into a quadtre object representing the upper left d by d 
//block of source
//
//inputs : source PNG image (dimensions greater than d)
//          integer resolution  (power of 2)
//
void Quadtree::buildTree(PNG const & source, int resolution)
{
    //free the space used by the original tree
    //recursive helper function necessary (deleteTree)
    deleteTree(root);
    
    imgsize = resolution;
    //recursive helper function necessary (buildhelper)
    root = buildHelper(source, 0, 0, imgsize);
    
    
}

//buildHelper recursive function
//builds quadtree of the source img
//
//inputs : source PNG
//          (x,y) coords of upper left corner of square to build
//          int d sidelength of square to build
//outputs : QuadtreeNode pointer to the root of the built tree
Quadtree::QuadtreeNode * Quadtree::buildHelper(const PNG & source, int x, int y, int d) const
{
    //basecase, make a leaf
    if (d == 1)
    {
    	QuadtreeNode * ret = new QuadtreeNode;
    	ret->element = *source(x,y);
    	ret->neChild = ret->nwChild = ret->swChild = ret->seChild = NULL;
    	//cout << ret->element << endl;
    	return ret;
    }
    
    //recursive case, make an "average" node
    
    QuadtreeNode * ret1 = new QuadtreeNode;
    
    //cout << d << endl;
    ret1->nwChild = buildHelper(source, x, y, d/2);
    ret1->neChild = buildHelper(source,x+d/2,y,d/2);
    ret1->swChild = buildHelper(source,x,y+d/2,d/2);
    ret1->seChild = buildHelper(source,x+d/2,y+d/2,d/2);
    
    //averaging
    ret1->element.red = (ret1->nwChild->element.red + ret1->neChild->element.red + ret1->seChild->element.red + ret1->swChild->element.red) / 4;
    ret1->element.blue = (ret1->nwChild->element.blue + ret1->neChild->element.blue + ret1->seChild->element.blue + ret1->swChild->element.blue) / 4;
    ret1->element.green = (ret1->nwChild->element.green + ret1->neChild->element.green + ret1->seChild->element.green + ret1->swChild->element.green) / 4;
    //cout << ret1->element << endl;
    return ret1;
}

//getPixel fuction
//
//returns the RGBAPixel at the given coordinates. note that if the quadtree
//specifically does not contain a node corresponding to this loc, get teh 
//pixel of the square region within which the smaller query grid cell would 
//lie.  E.g the element of the nonexistant leaf's deepest surviving ancestor.
//
//error check if coords are outside image or if empty.  Return RGBAPixel()
//
//inputs : int x, int y ( loocation of the pixel we want)
//
//outputs : RGBAPixel at that location
//
RGBAPixel Quadtree::getPixel(int x, int y) const
{
    //error checking
    if (x>=imgsize || y >= imgsize || imgsize == 0)
    {
        return RGBAPixel();
    }

    //get the pixel.  call a recursive helper (getHelper)
    return getHelper(root, x, y, 0, 0, imgsize);
}

//getHelper recursive pixel getter
//
//gets a pixel in a tree rooted at ptr
//
//inputs : ptr to node
//          (x,y) coords of pixel that we want
//          (dx,dy) coords of upper left corner of square currently being searched
//          int d sidelength of square
//outputs : RGBAPixel
RGBAPixel Quadtree::getHelper(QuadtreeNode * ptr, int x, int y, int dx, int dy, int d) const
{
    //just in case
    if (ptr == NULL)
    	{
    		return RGBAPixel();
    	}
    	
    //bascase, we have reached the leaf
    if (ptr->neChild == NULL || ptr->nwChild == NULL || ptr->seChild == NULL || ptr->swChild == NULL)
    {
    	//cout << ptr->element << endl;
    	return ptr->element;
    	
    }
    	//cout << dx << " " << dy << endl;
    //recursive case, we have to determine what quadrant to get the pixel from
     if (x < dx + d/2 && y < dy + d/2) // NW
    	return getHelper(ptr->nwChild,x,y,dx,dy,d/2);
    	
    else if (x >= dx+d/2 && y < dy + d/2) // NE
    	return getHelper(ptr->neChild,x,y,dx+d/2,dy,d/2);
    	
    else if (x < dx + d/2 && y >= dy + d/2) // SW
    	return getHelper(ptr->swChild,x,y,dx,dy+d/2,d/2);
    	
    else if (x >= dx + d/2 && y >= dy + d/2) // SE
    	return getHelper(ptr->seChild,x,y,dx+d/2,dy+d/2,d/2);
    	
    //there must be a problem....idk waht to return
    //cout << "wat?" << endl;
    return RGBAPixel();
    
}


//decompress function
//
//returns the underlying PNG object represented by the quadtree
//
//if the current tree is empty, return PNG()
//
//outputs : the PNG that the quadtree represents
//
PNG Quadtree::decompress() const
{
    if (imgsize == 0 || root == NULL)
        return PNG();

    PNG ret = PNG(imgsize,imgsize);
	//cout << "decomp1" << endl;
    //recursive helper function necessary, (decompHelper)
    decompHelper(root, ret, 0, 0, imgsize);

    return ret;
}

//decompress helper function, decompHelper
//
//decompresses the tree rooted at ptr.
//
//inputs : ptr to root node
//          (x,y) coords of the top left corner of a square to be decompressed
//          PNG & img pass the image by reference
//          int d sidelength of the square that ptr represents
void Quadtree::decompHelper(QuadtreeNode * ptr, PNG & img, int x, int y, int d) const
{
	//basecase, we are at a leaf
	if (ptr->neChild == NULL || ptr->nwChild == NULL || ptr->seChild == NULL || ptr->swChild == NULL)
	{
		//fill all pixels in the square of size d if we have reached a leaf
		int i = x;
		for (i = x; i < x + d;i++)
        {
		int j = y;
            for(j = y; j < y + d;j++)
            {
                *(img(i,j)) = ptr->element;
            }
        }
		//cout << ptr->element << x << ", " << y << endl;
		
		return;
	}
	
	else{
	//recurse until we reach a leaf
	decompHelper(ptr->nwChild, img, x,y,d/2);
	decompHelper(ptr->neChild, img, x+d/2,y,d/2);
	decompHelper(ptr->swChild, img, x,y+d/2,d/2);
	decompHelper(ptr->seChild, img, x+d/2,y+d/2,d/2);
	}
}



//prune function
//
//compresses the quadtree image by comparing the difference between the pixels below a node and 
//the value of the color of that node (average).  if this value is less than a tolerance, 
//then the node is "prunable"
//
//input : integer tolerance
//
void Quadtree::prune(int tolerance)
{
    pruneHelper(root, tolerance);
}

void Quadtree::pruneHelper(QuadtreeNode * temp, int tolerance) const
{
    //base case, we have already reached a leaf
    if (temp == NULL)
        return;
    
    //check if the node you are at is prunable, if so, prune!
    if (isPrunable(temp, tolerance, temp))
    {
        //cout << temp->nwChild->element << endl;
        //cout << temp->neChild->element << endl;
        //cout << temp->seChild->element << endl;
        //cout << temp->swChild->element << endl;
        //cout << temp->element << endl;
        
       // cout << "--------------------" << endl;

        deleteTree(temp->seChild);
        deleteTree(temp->swChild);
        deleteTree(temp->nwChild);
        deleteTree(temp->neChild);
        
        temp->nwChild = NULL;
        temp->neChild = NULL;
        temp->seChild = NULL;
        temp->swChild = NULL;
        return;
    } 
    
    pruneHelper(temp->nwChild, tolerance);
    pruneHelper(temp->neChild, tolerance);
    pruneHelper(temp->seChild, tolerance);
    pruneHelper(temp->swChild, tolerance);


}

//isPrunable function
//
//checks to see if a given node is prunable
//
//inputs : QuadtreeNode ptr, integer tolerance
//outputs : bool true if prunable, false if not
bool Quadtree::isPrunable(QuadtreeNode * temp, int tolerance, QuadtreeNode * avg) const
{
    if (temp == NULL)
        return true;

    //if not  at a leaf, recurse
    if (temp->nwChild != NULL)
    {
        return (isPrunable(temp->nwChild, tolerance, avg) && isPrunable(temp->neChild, tolerance, avg) &&
                isPrunable(temp->swChild, tolerance, avg) && isPrunable(temp->seChild, tolerance, avg));
    }
    //cout << temp->element << endl;
    //cout << temp->neChild->element << endl;
    //cout << temp->nwChild->element << endl;
    //cout << temp->swChild->element << endl;
    //cout << temp->seChild->element << endl;
    
    //if difference is too great, return false
    
    if (difference(temp->element, avg->element) > tolerance)
          return false;

    //otherwise the difference must be small, 
    return true;
}

//difference function for RGBAPixels
//
//inputs : two RGBAPixels
//
//outputs : the integer difference betwixt their colors
int Quadtree::difference(RGBAPixel px1, RGBAPixel px2) const
{
    int ret = 0;
    ret += pow(px1.red - px2.red, 2);
    ret += pow(px1.green - px2.green, 2);
    ret += pow(px1.blue - px2.blue, 2);
    return ret;
}

//
//pruneSize fucntion
//
//returns a count of the total number of leaves the quadtree would have
//if it were pruned as in the prune function
//
//input : int tolerance ( the tolerance that determines whether it can be 
//                         pruned)
//
//output : integer value of how many leaves the quadtree would have if pruned
//
int Quadtree::pruneSize(int tolerance) const
{
    return pruneSizeHelper(root, tolerance);
}

//pruneSizeHelper function
//
//takes in a node, determines the number of leaves that node would have if they were all pruned
//
//inputs : pointer to node, integer tolerance, int currTotal
//
//outputs : integer number of nodes if pruned
int Quadtree::pruneSizeHelper(QuadtreeNode * input, int tolerance) const
{
	if (input == NULL)
		return 0;
		
	//base case, reached a leaf, add a leaf to the total
    if (input->nwChild == NULL || isPrunable(input, tolerance, input))
    	return 1;

    return (pruneSizeHelper(input->nwChild, tolerance) + pruneSizeHelper(input->neChild, tolerance) + 
    		pruneSizeHelper(input->swChild, tolerance) + pruneSizeHelper(input->seChild, tolerance));
}

//idealPrune function
//
//given a number of leaves you want, determines the minimum tolerance necessary to prune a tree to 
//that number of leaves
//
//inputs : 
int Quadtree::idealPrune(int numLeaves) const
{
    int max = (255*255) + (255*255) + (255*255);
    int min = 0;
    int tol = (min + max) / 2;
    int curLeaves = 0;
    int lastval = max;
    
    
    while ((tol > min) && (tol < max))
    {
    	//tol = (min + max)/2;
        curLeaves = pruneSize(tol);
    	
    	//set guess value if curLeaves is no more than numLeaves
    	if (curLeaves <= numLeaves)
    	{
    		lastval = tol;
            max = tol;
        }
	
    	//curLeaves is too high, guess too low, make new min = guess
    	else// (curLeaves > numLeaves)
    	{
    		min = tol;
    	}
    	
	tol = (min + max)/2;
    }
    if (lastval == 1)
        lastval=0;
    return lastval;
}

//clockwiseRotate function
//
//stub out for now
//
void Quadtree::clockwiseRotate() 
{
	clockwiseHelper(root);
}

void Quadtree::clockwiseHelper(QuadtreeNode* temp) const
{
	//base case
		if (temp == NULL)
			return;
	//else rotate
		
		QuadtreeNode* nw = temp->nwChild;
		QuadtreeNode* ne = temp->neChild;
		QuadtreeNode* sw = temp->swChild;
		QuadtreeNode* se = temp->seChild;
		
		temp->nwChild = sw;
		temp->neChild = nw;
		temp->seChild = ne;
		temp->swChild = se;
		
		clockwiseHelper(nw);
		clockwiseHelper(ne);
		clockwiseHelper(sw);
		clockwiseHelper(se);
}
				
