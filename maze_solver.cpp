/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    maze_solver.cpp

    Code for the maze_solver class.  This class will use stack-based depth
    first search or queue-based breadth first search to find a solution (if
    one exists) to a simple maze.

    C. Painter-Wakefield
*/

///James Shima

#include "maze_solver.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;


// at maze_solver.h - you will need to modify it as well.  In this file you
// will need to complete several methods, and add any others as needed for your
// solution. 


/*
 _read_maze()

 Read in maze information (rows, columns, maze) from the provided input stream.
*/
void maze_solver::_read_maze(istream& in) {
    string first_line;
    string rows;
    string columns;
    getline(in, first_line);
    istringstream is(first_line);

    //rows and columns seperated via sstream;
    while(!is.eof()){
        is >> rows;
        _rows = stoi(rows);
        is >> columns;
        _columns = stoi(columns);
    }

    while(!in.eof()){
        string line = "";
        getline(in,line);
        _maze.push_back(line);
    }
}

/*
 _write_maze()

 Output the (partially or totally solved) maze on cout.
*/
void maze_solver::_print_maze() {
//    int rows = stoi(_maze.at(0));
//    rows+=2;

    for(int i =0; i<_rows; i++){
        cout << _maze.at(i) << endl;

    }
}

///Couldn't solve No wall problems but I tried for hours:(
bool maze_solver::outOfBounds(int x, int y) {
    int xplusone = x+1;
    int yplusone = y+1;
    int xminusone = x-1;
    int yminusone = y-1;
    if(x>=_rows || y>=_columns || y<0 || x<0 || xminusone>=_rows || yminusone>=_columns || yminusone<0 || xminusone<0 || xplusone>=_rows || yplusone>=_columns || yplusone<0 || xplusone<0){
        return true;
    }

    else return false;


}

/*
 _initialize()

 Find the start point.  Push or enqueue the start point.
*/
void maze_solver::_initialize() {
    for(int x = 0; x<_rows; x++){
        for(int y = 0; y<_columns; y++){
            //if(outOfBounds(&test_minusx,&test_minusy) || outOfBounds(&test_plusx,&test_plusy)) break;
            if(_maze.at(x).at(y) == 'o'){

                point start_point;
                start_point.x = x;
                start_point.y = y;


                //if(_columns%3==0) break;

                _stack_points.push(start_point);
                _queue_points.push(start_point);
                if(outOfBounds(x,y)){
                    _stack_points.pop();
                    _queue_points.pop();
                }

            }

        }
    }

}


/*
 _step()

 Take *one* step towards solving the maze, setting _no_more_steps and
 _goal_reached as appropriate.  This implements the essential maze search
 algorithm; take the next location from your stack or queue, mark the
 location with '@', add all reachable next points to your stack or queue,
 etc.

 Notes:

 - Your initial point should have been pushed/enqueued in the _initialize()
   method.

 - Set the _no_more_steps variable to true when there are no more reachable
   points, or when the maze was successfully solved.

 - Set the _goal_reached variable to true if/when the maze was successfully
   solved.

 - You should write an '@' over every location you have previously visited,
   *except* for the start and goal positions - they should remain 'o' and '*',
   respectively.

 - Since the run() method will call _print_maze() in between calls to _step(),
   you probably want to try to make progress on each call to step.  On some
   mazes, depending on your approach, it may be possible to add the same
   point multiple times to your stack or queue - i.e., if a point is reachable
   from multiple other points.  When this happens, your code will work, but
   it may make very slow progress.  To fix the problem, simply run a loop to
   remove any already visited points from your stack or queue at the beginning
   or end of _step().

 - There are many approaches to dealing with invalid/unreachable points; you
   can choose to add them and then remove them next time you get into _step(),
   you can choose to not add them in the first place, etc.

 - It is strongly recommended that you make helper methods to avoid code
   duplication; e.g., a function to detect that a point is out of bounds is
   a real help on the mazes with no walls.  You can also think about pulling
   out methods that do the actual acting on stacks/queues - this will reduce
   code duplication, since everything is identical between the two except
   for whether you use your stack or queue.  E.g., you could have methods
   named "_push", "_pop", "_next" which use the appropriate data structure.
*/




bool maze_solver::isEnd(int x, int y) {
    //int x = _stack_points.top().x;
    //int y = _stack_points.top().y;

    if(_maze.at(x).at(y+1) == '*'){
        return true;
    }
    else if(_maze.at(x).at(y-1) == '*'){
        return true;
    }
    else if(_maze.at(x+1).at(y) == '*'){
        return true;
    }
    else if(_maze.at(x-1).at(y) == '*'){
        return true;
    }
    else return false;
}

void maze_solver::_step() {

    //STACK _________ :
    if (_use_stack) {
        if (_stack_points.empty()) {
            _no_more_steps = true;
            return;
        }
        else if (isEnd(_stack_points.top().x,_stack_points.top().y)) {
            _no_more_steps = true;
            _goal_reached = true;
            return;
        }

        //Right:
        else if (_maze.at(_stack_points.top().x).at(_stack_points.top().y + 1) == '.') {
            _maze.at(_stack_points.top().x).at(_stack_points.top().y + 1) = '@';
            point next;
            next.x = _stack_points.top().x;
            next.y = _stack_points.top().y + 1;

            _stack_points.push(next);
            //if(outOfBounds(_stack_points.top().x,_stack_points.top().y)) _stack_points.pop();

        }
        //Up:
        else if (_maze.at(_stack_points.top().x + 1).at(_stack_points.top().y) == '.') {
            _maze.at(_stack_points.top().x + 1).at(_stack_points.top().y) = '@';
            point next;
            next.x = _stack_points.top().x + 1;
            next.y = _stack_points.top().y;

            _stack_points.push(next);
            //if(_columns%3==0) _stack_points.pop();
            //if(outOfBounds(_stack_points.top().x,_stack_points.top().y)) _stack_points.pop();

        }


        //Left:
        else if (_maze.at(_stack_points.top().x).at(_stack_points.top().y - 1) == '.') {
            _maze.at(_stack_points.top().x).at(_stack_points.top().y - 1) = '@';
            point next;
            next.x = _stack_points.top().x;
            next.y = _stack_points.top().y - 1;

            _stack_points.push(next);

            //if(outOfBounds(_stack_points.top().x,_stack_points.top().y)) _stack_points.pop();

        }



        //Down:
        else if (_maze.at(_stack_points.top().x - 1).at(_stack_points.top().y) == '.') {
            _maze.at(_stack_points.top().x - 1).at(_stack_points.top().y) = '@';
            point next;
            next.x = _stack_points.top().x - 1;
            next.y = _stack_points.top().y;

            _stack_points.push(next);

            //if(outOfBounds(_stack_points.top().x,_stack_points.top().y)) _stack_points.pop();
        }
        else {
            _stack_points.pop();
        }
    }

    //QUEUE __________ :
    else{

        if (_queue_points.empty()) {
            _no_more_steps = true;
            return;
        }
        if (isEnd(_queue_points.front().x,_queue_points.front().y)) {
            _no_more_steps = true;
            _goal_reached = true;
            return;
        }

        //Right:
        if (_maze.at(_queue_points.front().x).at(_queue_points.front().y + 1) == '.') {
            _maze.at(_queue_points.front().x).at(_queue_points.front().y + 1) = '@';
            point next;
            next.x = _queue_points.front().x;
            next.y = _queue_points.front().y + 1;
            _queue_points.push(next);


        }
        //Up:
        if (_maze.at(_queue_points.front().x + 1).at(_queue_points.front().y) == '.') {
            _maze.at(_queue_points.front().x + 1).at(_queue_points.front().y) = '@';
            point next;
            next.x = _queue_points.front().x + 1;
            next.y = _queue_points.front().y;

            _queue_points.push(next);

        }


        //Left:
        if (_maze.at(_queue_points.front().x).at(_queue_points.front().y - 1) == '.') {
            _maze.at(_queue_points.front().x).at(_queue_points.front().y - 1) = '@';
            point next;
            next.x = _queue_points.front().x;
            next.y = _queue_points.front().y - 1;

            _queue_points.push(next);

        }


        //Down:
        if (_maze.at(_queue_points.front().x - 1).at(_queue_points.front().y) == '.') {
            _maze.at(_queue_points.front().x - 1).at(_queue_points.front().y) = '@';
            point next;
            next.x = _queue_points.front().x - 1;
            next.y = _queue_points.front().y;

            _queue_points.push(next);
            //if(_columns%3==0) _queue_points.pop();

        }
        if(!_queue_points.empty()) {
            _queue_points.pop();
        }
    }
}
/***************************************************************************
    You should not need to modify code below this point.  Touch at your own
    risk!
****************************************************************************/

/*
 maze_solver constructor

 You should not need to modify this.  It opens the maze file and passes
 the input stream to read_maze(), along with setting up some internal state
 (most importantly, the variable telling you whether to use a stack or
 a queue).
*/
maze_solver::maze_solver(string infile, bool use_stak, bool pause) {
	_use_stack = use_stak;
	_do_pause = pause;

	_no_more_steps = false;
	_goal_reached = false;

	// parse out maze name for later use in creating output file name
	int pos = infile.find(".");
	if (pos == string::npos) {
		_maze_name = infile;
	} else {
		_maze_name = infile.substr(0, pos);
	}

	// open input file and read in maze
	ifstream fin(infile);

	_read_maze(fin);

	fin.close();
}

/*
 run()

 Initializes the maze_solver, then runs a loop to keep moving forward towards
 a solution.

 While more steps are possible (while no_more_steps == false), run() calls
 step(), then calls print_maze(), then pause().  Once there are no more steps,
 it prints a success/failure message to the user (based on the goal_reached 
 flag) and writes the final maze to a solution file.
*/

void maze_solver::run() {
    _initialize();

	cout << "Solving maze '" << _maze_name << "'." << endl;
	cout << "Initial maze: " << endl << endl;
	_print_maze();
	cout << endl;
	_pause();

	// main loop
	while (!_no_more_steps) {
		_step();
		cout << endl;
		_print_maze();
		cout << endl;
		_pause();
	}

	// final output to user
	cout << "Finished: ";
	if (_goal_reached) {
		cout << "goal reached!" << endl;
	} else {
		cout << "no solution possible!" << endl;
	}
}


/*
 pause()

 Pauses execution until user hits enter (unless do_pause == false).
*/
void maze_solver::_pause() {
	if (!_do_pause) return;
	string foo;
	cout << "Hit Enter to continue...";
	getline(cin, foo);
}

