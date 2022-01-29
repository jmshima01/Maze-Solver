/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    maze_solver.h

    Class declaration for the maze_solver class.

    C. Painter-Wakefield
*/

/// James Shima

#ifndef _MAZE_SOLVER_H
#define _MAZE_SOLVER_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/*
You need to fill in the following methods of this class:
    _read_maze()
    _print_maze()
    _initialize()
    _step()
 You will also need to add instance variables for your stack and queue
 objects.  You may also add other instance variables or methods as needed
 to effectively complete the task.  It is highly recommended that you also
 create helper methods to decompose and simplify your _step() method.

 The code below assumes you will use a vector<string> to store
 the maze. You can change this if you wish.
*/

class point{
public:
    //vars:
    int x;
    int y;

};

class maze_solver {
public:
    // constructor
	maze_solver(string infile, bool use_stak, bool pause = false);

	// public methods
	void run();

    //helper functions:

    //tests if goal is met in all directions of cur point:
    bool isEnd(int x, int y);

    //Checks if next point in any direction is not Out Of Bounds (via no wall mazes):
    //bool isValidS(int x, int y);

    bool outOfBounds(int x, int y);

private:
	// private instance variables
	string _maze_name;
	bool _use_stack;
	bool _do_pause;

	int _rows, _columns;
	vector<string> _maze;

	bool _no_more_steps;
	bool _goal_reached;

    //Stack And Queue of points(x,y):
    stack<point> _stack_points;
    queue<point> _queue_points;

	// private methods you need to write
    void _read_maze(istream& in);
    void _print_maze();
    void _initialize();
    void _step();

    // other private methods
    void _pause();
};
#endif
