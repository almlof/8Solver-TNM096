// lab1_astar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream> 
#include <queue> 
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map> 
#include <time.h>
#include <functional>

using namespace std;
const int PUZZLE_LENGTH = 9;
int SOLVED[PUZZLE_LENGTH] = { 1,2,3,4,5,6,7,8,0 };

class Puzzle
{
public:
	int state[PUZZLE_LENGTH];
	int gap_location;
	Puzzle(int a[PUZZLE_LENGTH])
	{
		for(int i = 0; i < PUZZLE_LENGTH; i++)
		{
			state[i] = a[i];
		}
	}
	Puzzle(const Puzzle &P)
	{
		for (int i = 0; i < PUZZLE_LENGTH; i++)
		{
			state[i] = P.state[i];
		}
		gap_location = P.gap_location;
	}

};

const Puzzle SOLVED_PUZZLE = {SOLVED};

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
		puzzle = new Puzzle(*C.puzzle);
		weight = C.weight;
		path = C.path;
		depth = C.depth;
	}
	/* Errors out atm 
	Node& operator = (Node &n)
	{
		std::cout << "copy assignment of A\n";
		std::swap(weight, n.weight);
		std::swap(puzzle, n.puzzle);
		std::swap(path, n.path);
		std::swap(depth, n.depth);
		return *this;
		
	}
	*/
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
	//cout << "move up" << endl;
	p->state[p->gap_location] = p->state[p->gap_location - 3]; //Update the switching var
	p->state[p->gap_location - 3] = 0;						   //Update the gap
	p->gap_location -= 3;
}
void move_down(Puzzle *p)
{
	//cout << "move down" << endl;
	p->state[p->gap_location] = p->state[p->gap_location + 3]; //Update the switching var
	p->state[p->gap_location + 3] = 0;						   //Update the gap

	p->gap_location += 3;
}

void move_left(Puzzle *p)
{
	//cout << "move left" << endl;
	p->state[p->gap_location] = p->state[p->gap_location - 1]; //Update the switching var
	p->state[p->gap_location - 1] = 0;						   //Update the gap

	p->gap_location -= 1;
}

void move_right(Puzzle *p)
{
	//cout << "move right" << endl;
//	cout << "This is gap location " << p->gap_location;
	p->state[p->gap_location] = p->state[p->gap_location + 1]; //Update the switching var
	p->state[p->gap_location + 1] = 0;						   //Update the gap
	p->gap_location = p->gap_location + 1;
	//cout << "This is gap location " << p->gap_location;
}
string get_config(Puzzle *p)
{
	string conf = "";
	for (int i = 0; i < PUZZLE_LENGTH; i++)
	{
		conf += p->state[i];
	}
	return conf;
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
/*Aux function for Manhattan dist func*/
int findRow(int i)
{
	int row = 0;

	if (i < 3)
	{
		row = 1;
	}
	else if (i < 6)
	{
		row = 2;
	}
	else
	{
		row = 3;
	}
	return row;
}

int m_cost(Puzzle *p)
{
	int dist = 0;
	for (int i = 0; i < PUZZLE_LENGTH; ++i)
	{
		int costs[PUZZLE_LENGTH] = {};

		for (int j = 0; j < PUZZLE_LENGTH; ++j)
		{
			if (p->state[i] == SOLVED_PUZZLE.state[j])
			{
				int col1 = i % 3;
				int col2 = j % 3;
				int row1 = findRow(i);
				int row2 = findRow(j);
				
				dist += abs(col1 - col2) + abs(row1 - row2);
				break;
			}
					
		}

	}
	return dist;
}

int main()
{

	/*Start timer*/
	clock_t tStart = clock();


	//Puzzle test1 = SOLVED_PUZZLE;
	int testSeries[PUZZLE_LENGTH] = {3,2,5,7,1,4,0,6,8 };
	Puzzle test1 = { testSeries };
	test1.gap_location = 6;
	Puzzle *p1 = &test1;
	
	/*Starting Node: zero weight and empty set of movements to come to this node*/
	Node *Start = new Node{ 0,p1,"",0};

	/*Initialize the min-heap out of Nodes with puzzelstates*/
	priority_queue <Node, vector<Node>, myComparator> pq;

	/*Adding hash table to map all the configurations we have gone trough*/
	unordered_map<string, bool> visited;

	pq.push(*Start);

	
	/* main loop */
	int counter = 0;
	
	while (true)
	{
		counter++;

		Node *top = new Node(pq.top());
		pq.pop();						//Remove the current one from the priority queue
		//print_puzzle(top->puzzle);
		
		/*check if we already checked this configuration*/
		string currentNodeConfig = get_config(top->puzzle);

		if (h_cost(top->puzzle) == 0 )
		{
			cout << top->path;
			break;
		}
		/*Add this Nodes puzzle configuration to the hashing table if it has not already been visited*/
		if (visited.find(currentNodeConfig) != visited.end())
		{
			continue;
		}
		else
		{
			visited[currentNodeConfig] = true;
		}
		if (can_move_down(top->puzzle->gap_location))
		{
			string dir = top->path + "D,";
			Node *child = new Node{ *top };
			child->path = dir;
			move_down(child->puzzle);
			child->weight += m_cost(child->puzzle) +1;
			pq.push(*child);
				
		}
		if (can_move_up(top->puzzle->gap_location))
		{
			string dir = top->path + "U,";
			Node *child = new Node{ *top };
			child->path = dir;
			move_up(child->puzzle);
			child->weight += m_cost(child->puzzle) +1;
			pq.push(*child);
			//update the cost 

		}
		if (can_move_right(top->puzzle->gap_location))
		{
			string dir = top->path + "R,";
			Node *child = new Node{ *top};
			child->path = dir;
			move_right(child->puzzle);
			child->weight += m_cost(child->puzzle) +1;
			pq.push(*child);

			//update the cost 
		}
	
		if (can_move_left(top->puzzle->gap_location))
		{
			string dir = top->path + "L,";
			Node *child = new Node{ *top };
			child->path = dir;
			move_left(child->puzzle);
			child->weight += m_cost(child->puzzle) +1;
			pq.push(*child);
			//update the cost 

		}
		
		delete top;//remove the current Node

	}
	
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
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




