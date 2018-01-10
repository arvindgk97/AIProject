#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <random>
#include "effolkronium/random.hpp"

using namespace std;
using Random = effolkronium::random_static;

struct block
{
	int surr=0;
	bool mines=false;
} ;

struct block * board[50][50];


void print(int size)
{
	for(int ctr=1;ctr<=size;ctr++)
	{
		cout<<"  ";
		cout<<ctr;
		if(ctr>=10)
		{

		}
		else
		{
			cout<<" ";
		}

	}
	cout<<"\n";
	for(int ctr1=1;ctr1<=size;ctr1++)
	{
		for(int ctr2=1;ctr2<=size;ctr2++)
		{
			cout<<"| ";
			cout<<board[ctr2][ctr1]->surr;
			cout<<" ";
		}
		cout<<"|";
		cout<<ctr1;
		cout<<"\n";
	}
}

void bomber(int bomb,int size)
{
	for(int ctr=1;ctr<=bomb;ctr++)
	{
		auto x = Random::get(1,size);
		auto y = Random::get(1,size);
		board[x][y]->mines=true;

		if(board[x][y-1]->mines==false && x>=1 && x<=size && y>=1 && y<=size)
		{
			board[x][y-1]->surr++;
		}

		if(board[x-1][y-1]->mines==false && x>=1 && x<=size && y>=1 && y<=size)
		{
			board[x-1][y-1]->surr++;
		}

		if(board[x+1][y-1]->mines==false && x>=1 && x<=size && y>=1 && y<=size)
		{
			board[x+1][y-1]->surr++;
		}

		if(board[x-1][y]->mines==false && x>=1 && x<=size && y>=1 && y<=size)
		{
			board[x-1][y]->surr++;
		}
		
		if(board[x+1][y]->mines==false && x>=1 && x<=size && y>=1 && y<=size)
		{
			board[x+1][y]->surr++;
		}
		
		if(board[x-1][y+1]->mines==false && x>=1 && x<=size && y>=1 && y<=size)
		{
			board[x-1][y+1]->surr++;
		}
		
		if(board[x][y+1]->mines==false && x>=1 && x<=size && y>=1 && y<=size)
		{
			board[x][y+1]->surr++;
		}
		
		if(board[x+1][y+1]->mines==false && x>=1 && x<=size && y>=1 && y<=size)
		{
			board[x+1][y+1]->surr++;
		}

		/*board[x-1][y-1]->surr++;

		board[x+1][y-1]->surr++;

		board[x-1][y]->surr++;

		board[x+1][y]->surr++;

		board[x-1][y+1]->surr++;

		board[x][y+1]->surr++;

		board[x+1][y+1]->surr++;*/

		print(size);
	}
}

void create(int size)
{

	for(int ctr=1;ctr<=size;ctr++)
	{
		for(int ctr1=1;ctr1<=size;ctr1++)
		{
			board[ctr1][ctr]=new block;
		}
	}
	print(size);
}

int main()
{
	int size;
	int bomb;
	cout<<"insert board size\n";
	cin>>size;
	create(size);
	cout<<"insert bomb\n";
	cin>>bomb;
	system("pause");

}
