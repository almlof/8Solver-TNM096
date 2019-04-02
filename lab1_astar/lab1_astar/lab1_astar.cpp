// lab1_astar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream> 
#include <queue> 
#include <algorithm>

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
void move_up(Puzzle *p)
{
	p->gap_location -= 3;

	for (int i = 0; i < 3; i++)
	{

	}
}
void move_down(Puzzle *p)
{
	p->gap_location += 3;
}

void move_left(Puzzle *p)
{
	p->gap_location -= 1;
}

void move_right(Puzzle *p)
{
	p->gap_location += 1;
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
		return false;
	return true;
}
bool can_move_right(int gap_location)
{
	if (gap_location != 2 && gap_location != 5 && gap_location != 8)
		return false;
	return true;
}

struct Node
{
	int weight;
	Puzzle *puzzle;
	string path;	 //Add to path
};

int main()
{
	Puzzle test1 = { { 1,8,2,0,4,3,7,6,5 } };
	Puzzle *p1 = &test1;
	cout << test1.state[0];

	priority_queue <

		/*
		priority_queue <int> gquiz;
		gquiz.push(10);
		gquiz.push(30);
		gquiz.push(20);
		gquiz.push(5);
		gquiz.push(1);

		cout << "The priority queue gquiz is : ";
		showpq(gquiz);

		cout << "\ngquiz.size() : " << gquiz.size();
		cout << "\ngquiz.top() : " << gquiz.top();


		cout << "\ngquiz.pop() : ";
		gquiz.pop();
		showpq(gquiz);
		*/
		return 0;
}




