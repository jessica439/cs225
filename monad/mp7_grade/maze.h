#ifndef _MAZE_H_
#define _MAZE_H_

#include "png.h"
#include "dsets.h"
#include <vector>

class SquareMaze{
	public:
		//makeMaze()
		//makes a square maze
		//takes width and height as parameters
		//doesnt return anything
		void makeMaze(int width, int height);

		//returns whether or not it is possible to go in 
		//given direction at given coordinates
		//0=right
		//1=down
		//2=left
		//3=up
		//takes coordinates and direction (all ints)
		//returns a boolean
		bool canTravel(int x, int y, int dir) const;

		//setWall()
		//sets whether or not specified wall exists
		void setWall(int x, int y, int dir, bool exists);

		//solveMaze()
		//solves the maze
		//takes no parameters
		//returns a vector of directions that solves maze
		vector<int> solveMaze();

		//drawMaze()
		//draws the maze without the solution
		//returns a PNG pointer
		//takes no params
		PNG * drawMaze()const;

		//drawMazeWithSolution()
		//draws the maze WITH solution
		//returns a png pointer
		//takes no params
		PNG * drawMazeWithSolution();
	
	private:
		std::vector<int> DFS(int x, int y, int fromdir)const;

		int idx(int x, int y) const;

		class Cell{
			public:
				Cell(){
					right =1;
					bottom = 1;
				}
				bool right;
				bool bottom;
		};

		int width;
		int height;

		std::vector<Cell> cells;

};
#endif
