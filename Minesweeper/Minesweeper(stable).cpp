#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <random>
#include "effolkronium/random.hpp"

using namespace std;;
using Random = effolkronium::random_static;

struct block
{
	int surr=0;
	bool mines=false;
	char flag='.';
	int status=0;
	int prob;
};

int checkx[9] = {0,1,1,0,-1,-1,-1,0,1};
int checky[9] = {0,0,1,1,1,0,-1,-1,-1};
int bomb;
struct block * board[50][50];
int size;
int spam=0;

void answer()
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
                if(board[ctr2][ctr1]->surr>=1)
                {
                    cout<<board[ctr2][ctr1]->surr;
                }
                else
                {
                    cout<<board[ctr2][ctr1]->flag;
                }
            }
            else
            {
                if(board[ctr2][ctr1]->flag=='!')
                {
                    if(board[ctr2][ctr1]->mines==true)
                    {
                        cout<<"*";
                    }
                    else
                    {
                        cout<<board[ctr2][ctr1]->flag;
                    }
                }
                else
                {
                    if(board[ctr2][ctr1]->mines==true)
                    {
                        cout<<"*";
                    }
                    else
                    {
                        cout<<board[ctr2][ctr1]->status;
                    }
                }
            }
            cout<<" ";
        }
        cout<<"|";
        cout<<ctr1;
        cout<<"\n";
    }
    cout<<"bomb left = "<<bomb<<"\n";
}

void print()
{
    int block=0;
    spam=0;
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
                if(board[ctr2][ctr1]->surr>=1)
                {
                    cout<<board[ctr2][ctr1]->surr;
                }
                else
                {
                    cout<<board[ctr2][ctr1]->flag;
                }
            }
            else
            {
                block++;
                if(board[ctr2][ctr1]->flag=='!')
                {
                    spam++;
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
    }
    cout<<"bomb left = "<<bomb<<"\n";
    if(spam>bomb)
    {

    }
    else
    {
        if(bomb==block)
        {
            answer();
            bomb=0;
        }
    }
}

void flood(int x, int y)
{
	for(int ctr=1;ctr<=8;ctr++)
	{
		int newx=x+checkx[ctr];
		int newy=y+checky[ctr];
		if(newx<1 || newy<1 || newx>size || newy>size)
		{
			continue;
		}
		if(board[newx][newy]->surr>=1)
		{
			board[newx][newy]->status=1;
			continue;
		}
		if(board[newx][newy]->status==1)
        {
            continue;
        }
		if(board[newx][newy]->status==0)
		{
			board[newx][newy]->status=1;
			print();
			flood(newx,newy);
		}
	}
}

void flag()
{
	int x;
	int y;
	cout<<"enter coordinate separated by space\n";
	cin>>x>>y;
	if(board[x][y]->flag=='!')
    {
        if(board[x][y]->mines==false)
        {
            bomb++;
            board[x][y]->flag='.';
        }
        else
        {
            board[x][y]->flag='.';
        }
    }
    else
    {
        if(board[x][y]->mines==true)
        {
            if(spam>bomb)
            {
                board[x][y]->flag='!';
            }
            else
            {
                bomb--;
                board[x][y]->flag='!';
            }

        }
        else
        {
            board[x][y]->flag='!';
        }
    }
	print();
}

void open()
{
	int x;
	int y;
	cout<<"enter coordinate separated by space\n";
	cin>>x>>y;
	if(board[x][y]->mines==false)
	{
		if(board[x][y]->surr>=1)
        {
            board[x][y]->status=1;
            print();
        }
        else
        {
            board[x][y]->status=1;
            flood(x,y);
            print();
        }
	}
	else
	{
		answer();
		cout<<"you lost\n";
		print();
		exit(0);
	}
}

void bomber()
{
	for(int ctr=1;ctr<=bomb;ctr++)
	{
		auto x = Random::get(1,size);
		auto y = Random::get(1,size);
		board[x][y]->mines=true;

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
	}
}

void create()
{
	for(int ctr=1;ctr<=size;ctr++)
	{
		for(int ctr1=1;ctr1<=size;ctr1++)
		{
			board[ctr1][ctr]=new block;
		}
	}
	print();
}

void scan()
{
    int block=0;
    spam=0;
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
                if(board[ctr2][ctr1]->surr>=1)
                {
                    cout<<board[ctr2][ctr1]->surr;
                }
                else
                {
                    cout<<board[ctr2][ctr1]->flag;
                }
            }
            else
            {
                block++;
                if(board[ctr2][ctr1]->flag=='!')
                {
                    spam++;
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
    }
    cout<<"bomb left = "<<bomb<<"\n";
}

int main()
{
	int choice;
	cout<<"insert board size\n";
	cin>>size;
	create();
	cout<<"insert bomb\n";
	cin>>bomb;
	bomber();
	while(bomb!=0)
	{
		cout<<"open(1) || flag(2) || cheat(3)?\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
				open();
				break;
			case 2:
				flag();
				break;
			case 3:
				answer();
				break;
		}
	}
	cout<<"you won";
}
