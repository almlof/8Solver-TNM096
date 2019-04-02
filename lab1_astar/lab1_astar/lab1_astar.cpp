// lab1_astar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream> 
#include <queue> 
#include <algorithm>
#include <string>

using namespace std;
const int PUZZLE_LENGTH = 9;
const int MAXILON = 100000;

struct Puzzle
{
	int state[PUZZLE_LENGTH];
	int gap_location;
};


const Puzzle SOLVED_PUZZLE = { { 1,2,3,4,5,6,7,8,0 } };
bool visited[MAXILON] = { false };

void showpq(priority_queue <int> gq)
{
	priority_queue <int> g = gq;
	while (!g.empty())
	{
		cout << '\t' << g.top();
		g.pop();
	}
	cout << '\n';
}


bool can_move_down(int gap_location)
{
	if (gap_location < 6)
		return true;
	return false;
}
bool can_move_left(int gap_location)
{
	if (gap_location != 0 && gap_location != 3 && gap_location != 6)
		return false;
	return true;
}
bool can_move_right(int gap_location)
{
	if (gap_location != 2 && gap_location != 5 && gap_location != 8)
		return false;
	return true;
}

/*Nodes containing the state of the current configuration */
struct Node
{
	int weight;
	Puzzle *puzzle;
	string path;	//Add to path
};
/* Function to compare weights of each node in the heap*/
class myComparator
{
public:
	int operator() (const Node& n1, const Node& n2)
	{
		return n1.weight > n2.weight;
	}
};

/*Function(s) to move puzzle digit*/
void move_up(Puzzle *p)
{
	p->state[p->gap_location] = p->state[p->gap_location - 3]; //Update the switching var
	p->state[p->gap_location - 3] = 0;						   //Update the gap
	
	p->gap_location -= 3;
}
void move_down(Puzzle *p)
{
	p->state[p->gap_location] = p->state[p->gap_location + 3]; //Update the switching var
	p->state[p->gap_location + 3] = 0;						   //Update the gap

	p->gap_location += 3;
}

void move_left(Puzzle *p)
{
	p->state[p->gap_location] = p->state[p->gap_location - 1]; //Update the switching var
	p->state[p->gap_location - 1] = 0;						   //Update the gap

	p->gap_location -= 1;
}

void move_right(Puzzle *p)
{
	p->state[p->gap_location] = p->state[p->gap_location + 1]; //Update the switching var
	p->state[p->gap_location + 1] = 0;						   //Update the gap
	p->gap_location += 1;
}

int main()
{
	Puzzle test1 = { { 1,8,2,0,4,3,7,6,5 } };
	Puzzle *p1 = &test1;
	
	/*Starting Node: zero weight and empty set of movements to come to this node*/
	Node Start = { 0,p1,"" };

	/*Initialize the min-heap out of  Nodes with puzzelstates*/
	priority_queue <Node, vector<Node>, myComparator> pq;

	pq.push(Start);
	/*main loop */
	while (true)
	{
		Node top = pq.top();
		if (can_move_down(top.puzzle->gap_location))
			{
				
				//move down and evaluate the cost according to the heuristic function
				
			}

	}
	
	// One by one extract items from min heap 
	while (pq.empty() == false)
	{
		Node p = pq.top();
		cout << "(" << p.weight << ", " << p.path << ")";
		cout << endl;
		pq.pop();
	}


		return 0;
}




