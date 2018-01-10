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
	char flag='O';
	int status=0;
};

int total=0;
struct block * board[50][50];
int size;

void flag()
{
	int x;
	int y;
	cout<<"enter coordinate\n";
	cin>>x>>y;
	board[x][y]->flag='!';
}

void flood(int x, int y)
{
	if(y!=1)
	{
		if(board[x][y-1]->surr>=1)
		{
			board[x][y-1]->status=1;
			total--;
			flood(x-1,y-1);
			flood(x+1,y-1);
			flood(x-1,y);
			flood(x+1,y);
			flood(x-1,y+1);
			flood(x,y+1);
			flood(x+1,y+1);
		}
		else
		{
			board[x][y-1]->status=1;
			total--;
			flood(x,y-1);
		}
	}
	if(x!=1 && y!=1)
	{
		if(board[x-1][y-1]->mines==false)
		{
			board[x-1][y-1]->status=1;
		}
	}
	if(x!=size && y!=1)
	{
		if(board[x+1][y-1]->mines==false)
		{
			board[x+1][y-1]->status=1;
		}
	}
	if(x!=1)
	{
		if(board[x-1][y]->mines==false)
		{
			board[x-1][y]->status=1;
		}
	}
	if(x!=size)
	{
		if(board[x+1][y]->mines==false)
		{
			board[x+1][y]->status=1;
		}
	}
	if(x!=1 && y!=size)
	{
		if(board[x-1][y+1]->mines==false)
		{
			board[x-1][y+1]->status=1;
		}
	}
	if(y!=size)
	{
		if(board[x][y+1]->mines==false)
		{
			board[x][y+1]->status=1;
		}
	}
	if(x!=size && y!=size)
	{
		if(board[x+1][y+1]->mines==false)
		{
			board[x+1][y+1]->status=1;
		}
	}
}

void open()
{
	int x;
	int y;
	cout<<"enter coordinate\n";
	cin>>x>>y;
	if(board[x][y]->mines==false)
	{
		board[x][y-1]->status=1;
		total--;
		flood(x,y);
	}
	else
	{
		cout<<"you lost";
		exit(0);
	}
}

void print()
{
	for(int ctr=1;ctr<=size;ctr++)
	{
		cout<<"  ";
		cout<<ctr;
		if(ctr>=!10)
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
			if(board[ctr2][ctr1]->status==1)
			{
				cout<<board[ctr2][ctr1]->surr;
			}
			else
			{
				if(board[ctr2][ctr1]->flag=='!')
				{
					cout<<board[ctr2][ctr1]->flag;
				}
				else
				{
					cout<<board[ctr2][ctr1]->status;
				}
			}
			cout<<" ";
		}
		cout<<"|";
		cout<<ctr1;
		cout<<"\n";
		cout<<total;
	}
}

void bomber(int bomb)
{
	for(int ctr=1;ctr<=bomb;ctr++)
	{
		auto x = Random::get(1,size);
		auto y = Random::get(1,size);
		board[x][y]->mines=true;
		total--;
		if(y!=1)
		{
			if(board[x][y-1]->mines==false)
			{
				board[x][y-1]->surr++;
			}
		}
		if(x!=1 && y!=1)
		{
			if(board[x-1][y-1]->mines==false)
			{
				board[x-1][y-1]->surr++;
			}
		}
		if(x!=size && y!=1)
		{
			if(board[x+1][y-1]->mines==false)
			{
				board[x+1][y-1]->surr++;
			}
		}
		if(x!=1)
		{
			if(board[x-1][y]->mines==false)
			{
				board[x-1][y]->surr++;
			}
		}
		if(x!=size)
		{
			if(board[x+1][y]->mines==false)
			{
				board[x+1][y]->surr++;
			}
		}
		if(x!=1 && y!=size)
		{
			if(board[x-1][y+1]->mines==false)
			{
				board[x-1][y+1]->surr++;
			}
		}
		if(y!=size)
		{
			if(board[x][y+1]->mines==false)
			{
				board[x][y+1]->surr++;
			}
		}
		if(x!=size && y!=size)
		{
			if(board[x+1][y+1]->mines==false)
			{
				board[x+1][y+1]->surr++;
			}
		}
		print();
	}
}

void create()
{

	for(int ctr=1;ctr<=size;ctr++)
	{
		for(int ctr1=1;ctr1<=size;ctr1++)
		{
			board[ctr1][ctr]=new block;
			total++;
		}
	}
	print();
}

int main()
{
	int size;
	int bomb;
	cout<<"insert board size\n";
	cin>>size;
	create();
	cout<<"insert bomb\n";
	cin>>bomb;
	bomber(bomb);
	while(total!=0)
	{
		cout<<"open(1) or flag(2)?\n";
		switch(1)
		{
			case 1:
				open();
			case 2:
				flag();
		}
	}
	cout<<"you won";
}
