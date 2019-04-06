// lab1_astar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream> 
#include <queue> 
#include <algorithm>
#include <string>
#include <vector>

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

bool can_move_up(int gap_location)
{
	if (gap_location > 2)
		return true;
	return false;
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
		return true;
	return false;
}
bool can_move_right(int gap_location)
{
	if (gap_location != 2 && gap_location != 5 && gap_location != 8)
		return true;
	return false;
}

/*Nodes containing the state of the current configuration */

void print_puzzle(Puzzle *p)
{
	for (int i = 0;i < PUZZLE_LENGTH;i++)
	{
		if (i % 3 == 0)
			cout << endl;

		cout << p->state[i] << " , ";
	}
	cout << endl;
}
class Node
{
public:
	Node(int _weight, Puzzle *_puzzle, string _path, int _depth)
	{
		weight = _weight;
		puzzle = _puzzle;
		path = _path;
		depth = _depth;
	}
	Node(const Node &C)
	{
		weight = C.weight;
		puzzle = C.puzzle;
		path = C.path;
		depth = C.depth;
	}
	//Node clone() { return Node(*this); }
	
	int weight;
	Puzzle *puzzle;
	string path;	
	int depth;
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
	cout << "move up" << endl;
	p->state[p->gap_location] = p->state[p->gap_location - 3]; //Update the switching var
	p->state[p->gap_location - 3] = 0;						   //Update the gap
	
	p->gap_location -= 3;
}
void move_down(Puzzle *p)
{
	cout << "move down" << endl;
	p->state[p->gap_location] = p->state[p->gap_location + 3]; //Update the switching var
	p->state[p->gap_location + 3] = 0;						   //Update the gap

	p->gap_location += 3;
}

void move_left(Puzzle *p)
{
	cout << "move left" << endl;
	p->state[p->gap_location] = p->state[p->gap_location - 1]; //Update the switching var
	p->state[p->gap_location - 1] = 0;						   //Update the gap

	p->gap_location -= 1;
}

void move_right(Puzzle *p)
{
	cout << "move right" << endl;
//	cout << "This is gap location " << p->gap_location;
	p->state[p->gap_location] = p->state[p->gap_location + 1]; //Update the switching var
	p->state[p->gap_location + 1] = 0;						   //Update the gap
	p->gap_location = p->gap_location + 1;
	//cout << "This is gap location " << p->gap_location;
}

int h_cost(Puzzle *p)
{
	int h_cost = 0;

	for (int i = 0; i < PUZZLE_LENGTH; ++i)
	{
		if (p->state[i] == 0)
		{
			continue;
		}
		if (p->state[i] != SOLVED_PUZZLE.state[i])
		{
			h_cost += 1;
		}
	}
	return h_cost;
}

int main()
{
	//Puzzle test1 = SOLVED_PUZZLE;
	Puzzle test1 = { { 1,8,2,0,4,3,7,6,5 } };
	test1.gap_location = 3;
	Puzzle *p1 = &test1;
	
	/*Starting Node: zero weight and empty set of movements to come to this node*/
	Node *Start = new Node{ 0,p1,"",0};

	/*Initialize the min-heap out of  Nodes with puzzelstates*/
	priority_queue <Node, vector<Node>, myComparator> pq;

	pq.push(*Start);
	
	/*main loop */
	int counter = 0;

	while (true)
	{
		counter++;

		Node *top = new Node(pq.top());
		print_puzzle(top->puzzle);
		

		if (h_cost(top->puzzle) == 0 || counter > 5)
		{
			break;
		}
		if (can_move_down(top->puzzle->gap_location))
		{
			string dir = top->path + "D,";
			Node *child = new Node{ *top };
			child->path = dir;
			child->weight = top->weight + 1;

			move_down(child->puzzle);
			child->weight += h_cost(child->puzzle);
			pq.push(*child);
				
		}
		if (can_move_up(top->puzzle->gap_location))
		{
			string dir = top->path + "U,";
			Node *child = new Node{ *top };
			move_up(child->puzzle);
			child->weight += h_cost(child->puzzle);
			pq.push(*child);
			//update the cost 

		}
		if (can_move_right(top->puzzle->gap_location))
		{
			
			string dir = top->path + "R,";
			Node *child = new Node{ *top};
			move_right(child->puzzle);
			child->weight += h_cost(child->puzzle);
			pq.push(*child);

			//update the cost 

		}
		if (can_move_left(top->puzzle->gap_location))
		{
			string dir = top->path + "L,";
			Node *child = new Node{ *top };
			move_left(child->puzzle);
			child->weight += h_cost(child->puzzle);
			pq.push(*child);
			//update the cost 

		}
	
		pq.pop(); //pop the top


	}
	cout << "finished";
	// One by one extract items from min heap 
	/*
	while (pq.empty() == false)
	{
		Node p = pq.top();
		cout << "(" << p.weight << ", " << p.path << ")";
		cout << endl;
		pq.pop();
	}
	*/

return 0;
}




