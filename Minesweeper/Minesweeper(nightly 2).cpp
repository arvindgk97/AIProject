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
	int prob=0;
};

struct aibrain
{
    int prob=0;
};
int checkx[9] = {0,1,1,0,-1,-1,-1,0,1};
int checky[9] = {0,0,1,1,1,0,-1,-1,-1};

int aistop=0;
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

void printprob()
{
    cout<<"Displaying Ai's Eye"<<endl;
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
                    cout<<"X";
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
                    cout<<board[ctr2][ctr1]->flag;
                }
                else
                {
                    if(board[ctr2][ctr1]->prob>=1)
                    {
                        cout<<board[ctr2][ctr1]->prob;
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


void aiscan()
{
    for(int ctr1=1;ctr1<=size;ctr1++)
    {
        for(int ctr2=1;ctr2<=size;ctr2++)
        {
            board[ctr2][ctr1]->prob=0;
        }
    }
    for(int ctr1=1;ctr1<=size;ctr1++)
    {
        for(int ctr2=1;ctr2<=size;ctr2++)
        {
            if(board[ctr2][ctr1]->status==1)
            {
                if(board[ctr2][ctr1]->surr>=1)
                {
                    for(int ctr3=1;ctr3<=8;ctr3++)
                    {
                        int newx=ctr2+checkx[ctr3];
                        int newy=ctr1+checky[ctr3];
                        if(newx<1 || newy<1 || newx>size || newy>size)
                        {
                            continue;
                        }
                        if(board[newx][newy]->surr>=1)
                        {
                            if(board[newx][newy]->status==0)
                            {
                                board[newx][newy]->prob=board[newx][newy]->prob+board[ctr2][ctr1]->surr;
                                continue;
                            }
                            else
                            {
                                if(board[newx][newy]->prob>=1)
                                {
                                    board[newx][newy]->prob=0;
                                    continue;
                                }
                                else
                                {
                                    continue;
                                }
                            }
                        }
                        if(board[newx][newy]->status==1)
                        {
                            continue;
                        }
                        if(board[newx][newy]->status==0)
                        {
                            board[newx][newy]->prob=board[newx][newy]->prob+board[ctr2][ctr1]->surr;
                        }
                    }
                }
            }
        }
    }
    printprob();
}

void aiopen()
{
    int x2[100];
    int y2[100];
    int ctr3=1;
    int x;
    int y;
    for(int ctr1=1;ctr1<=size;ctr1++)
    {
        for(int ctr2=1;ctr2<=size;ctr2++)
        {
            if(board[ctr2][ctr1]->status==0)
            {
                x2[ctr3]=ctr2;
                y2[ctr3]=ctr1;
                ctr3++;
            }
        }
    }
    auto aichoose = Random::get(1,ctr3);
    x=x2[aichoose];
    y=y2[aichoose];
    if(board[x][y]->status==0)
    {
        cout<<"open coordinate = "<<x<<" , "<<y<<"\n";
        if(board[x][y]->mines==false)
        {
            if(board[x][y]->surr>=1)
            {
                board[x][y]->status=1;
                aiopen();
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
            cout<<"ai lost\n";
            exit(0);
        }
    }
}

aianswer(int newlowx, int newlowy)
{
    //ai open a block based on the lowest probability
    cout<<"open coordinate = "<<newlowx<<" , "<<newlowy<<"\n";
    if(board[newlowx][newlowy]->mines==false)
    {
        if(board[newlowx][newlowy]->surr>=1)
        {
            board[newlowx][newlowy]->status=1;
            print();
        }
        else
        {
            board[newlowx][newlowy]->status=1;
            flood(newlowx,newlowy);
            print();
        }
    }
    else
    {
        answer();
        cout<<"ai lost\n";
        exit(0);
    }
}

aiscrounge(int newlowx,int newlowy)
{
    //ai scrounge for any 3x3 size unopened box first before using any probability and skip a flagged block
    int boxx[9]={0,0,0,1,1,1,2,2,2};
    int boxy[9]={0,1,2,0,1,2,0,1,2};
    int box=0;
    for(int ctr1=1;ctr1<=size;ctr1++)
    {
        for(int ctr2=1;ctr2<=size;ctr2++)
        {
            if(board[ctr2][ctr1]->flag!='!')
            {
                if(board[ctr2][ctr1]->status==0)
                {
                    for(int ctr=1;ctr<=9;ctr++)
                    {
                        int newx=ctr2+boxx[ctr];
                        int newy=ctr1+boxy[ctr];
                        if(newx<1 || newy<1 || newx>size || newy>size)
                        {
                            box=0;
                            //cout<<"hit a wall"<<endl;
                            continue;
                        }
                        if(board[newx][newy]->surr>=1)
                        {
                            box=0;
                            //cout<<"hit a number"<<endl;
                            continue;
                        }
                        if(board[newx][newy]->status==1)
                        {
                            box=0;
                            //cout<<"hit an opened box"<<endl;
                            continue;
                        }
                        if(board[newx][newy]->status==0)
                        {
                            box++;
                            //cout<<"box++ "<<newx<<" , "<<newy<<"\n";
                            if(box==8)
                            {
                                cout<<"3x3 detected"<<"\n";
                                cout<<"open coordinate = "<<ctr2<<" , "<<ctr1<<"\n";
                                if(board[ctr2][ctr1]->mines==false)
                                {
                                    if(board[ctr2][ctr1]->surr>=1)
                                    {
                                        board[ctr2][ctr1]->status=1;
                                        aiscrounge(newlowx, newlowy);
                                        print();
                                    }
                                    else
                                    {
                                        board[ctr2][ctr1]->status=1;
                                        flood(ctr2,ctr1);
                                        print();
                                    }
                                }
                                else
                                {
                                    answer();
                                    cout<<"ai lost\n";
                                    exit(0);
                                }
                                box=0;
                            }
                        }
                    }
                }
            }
        }
    }
    aianswer(newlowx,newlowy);
}

void aiflagcheck()
{
    //ai scans if there any move he could do
    for(int ctr1=1;ctr1<=size;ctr1++)
    {
        for(int ctr2=1;ctr2<=size;ctr2++)
        {
            if(board[ctr2][ctr1]->status==0)
            {
                if(board[ctr2][ctr1]->flag!='!')
                {
                    if(board[ctr2][ctr1]->mines==false)
                    {
                        return;
                    }
                }
            }
        }
    }
    cout<<"the AI couldn't do anything at this point\n";
    exit(0);
}

aiobvious()
{
    int obvious=0;
    int x2[100];
    int y2[100];
    //check around
    for(int ctr1=1;ctr1<=size;ctr1++)
    {
        for(int ctr2=1;ctr2<=size;ctr2++)
        {
            if(board[ctr2][ctr1]->status==1)
            {
                if(board[ctr2][ctr1]->flag!='!')
                {
                    if(board[ctr2][ctr1]->surr>=1)
                    {
                        for(int ctr=1;ctr<=8;ctr++)
                        {
                            int newx=ctr2+checkx[ctr];
                            int newy=ctr1+checky[ctr];
                            if(newx<1 || newy<1 || newx>size || newy>size)
                            {
                                continue;
                            }
                            if(board[newx][newy]->surr>=1)
                            {
                                continue;
                            }
                            if(board[newx][newy]->status==1)
                            {
                                continue;
                            }
                            if(board[newx][newy]->flag=='!')
                            {

                                obvious++;
                                x2[obvious]=newx;
                                y2[obvious]=newy;
                                continue;
                            }
                            if(board[newx][newy]->status==0)
                            {
                                obvious++;
                                x2[obvious]=newx;
                                y2[obvious]=newy;
                            }
                        }
                    }
                }
            }
            if(obvious==board[ctr2][ctr1]->surr)
            {
                //cout<<"obvious found"<<endl;
                for(int ctr=1;ctr<=obvious;obvious++)
                {
                    if(board[x2[ctr]][y2[ctr]]->flag=='!')
                    {
                        continue;
                    }
                    if(board[x2[ctr]][y2[ctr]]->status==0)
                    {
                        if(board[x2[ctr]][y2[ctr]]->mines==true)
                        {
                            bomb--;
                            cout<<"flagging obvious coordinate = "<<x2[ctr]<<" , "<<y2[ctr]<<"\n";
                            board[x2[ctr]][y2[ctr]]->flag='!';
                            if(bomb==0)
                            {
                                cout<<"AI Wins"<<endl;
                                print();
                                exit(0);
                            }
                            print();
                            aiflagcheck();
                            aiobvious;
                        }
                        else
                        {
                            cout<<"flagging obvious coordinate = "<<x2[ctr]<<" , "<<y2[ctr]<<"\n";
                            board[x2[ctr]][y2[ctr]]->flag='!';
                            cout<<"AI Missed The Flag"<<endl;
                            if(bomb==0)
                            {
                                cout<<"AI Wins"<<endl;
                                print();
                                exit(0);
                            }
                            print();
                            aiflagcheck();
                            aiobvious;
                        }
                    }
                }
            }
        }
    }
}

void aithink()
{
    int low=0;
    int calc[50];
    int ctr3=1;
    int lowlim=10;
    int highlim=1;
    int high=0;
    int x2[100];
    int y2[100];
    float chance;
    //scan the board and collect the coordinate for any probability it carries but skips a flagged board
    for(int ctr1=1;ctr1<=size;ctr1++)
    {
        for(int ctr2=1;ctr2<=size;ctr2++)
        {
            if(board[ctr2][ctr1]->flag!='!')
            {
                if(board[ctr2][ctr1]->status==0)
                {
                    if(board[ctr2][ctr1]->prob>=1)
                    {
                        x2[ctr3]=ctr2;
                        y2[ctr3]=ctr1;
                        calc[ctr3]=board[ctr2][ctr1]->prob;
                        ctr3++;
                    }
                }
            }
        }
    }
    //calculate for the lowest and highest probability found with coord
    for(int ctr4=1; ctr4 < ctr3; ctr4++)
    {
        if (calc[ctr4] < lowlim)
        {
            lowlim = calc[ctr4];
            low=ctr4;
        }
        if (calc[ctr4] > highlim)
        {
            highlim = calc[ctr4];
            high=ctr4;
        }
    }
    int newlowx=x2[low];
    int newlowy=y2[low];
    int newhighx=x2[high];
    int newhighy=y2[high];
    cout<<"The lowest prob is: "<<lowlim<<". coordinate is "<<newlowx<<" , "<<newlowy<<"\n";
    cout<<"The highest prob is: "<<highlim<<". coordinate is "<<newhighx<<" , "<<newhighy<<"\n";
    // if yield same result ai will try to find a large 3x3 size unopened box
    if(lowlim==highlim)
    {
        if(newlowx==newhighx)
        {
            if(newlowy==newhighy)
            {
                if(board[newhighx][newhighy]->mines==true)
                {
                    bomb--;
                    cout<<"flagging coordinate = "<<newhighx<<" , "<<newhighy<<"\n";
                    if(bomb==0)
                    {
                        cout<<"AI Wins"<<endl;
                        print();
                        exit(0);
                    }
                    board[newhighx][newhighy]->flag='!';
                }
                else
                {
                    cout<<"flagging coordinate = "<<newhighx<<" , "<<newhighy<<"\n";
                    board[newhighx][newhighy]->flag='!';
                    cout<<"AI Missed The Flag"<<endl;
                    if(bomb==0)
                    {
                        cout<<"AI Wins"<<endl;
                        print();
                        exit(0);
                    }
                }
                    print();
                    aiflagcheck();
            }
        }
        else
        {
            aiobvious();
            aiscrounge(newlowx,newlowy);
            aiscan();
        }
    }
    else
    {
        //ai will automatically flag a high probability block
        if(board[newhighx][newhighy]->mines==true)
        {
            bomb--;
            cout<<"flagging coordinate = "<<newhighx<<" , "<<newhighy<<"\n";
            board[newhighx][newhighy]->flag='!';
            if(bomb==0)
            {
                cout<<"AI Wins"<<endl;
                print();
                exit(0);
            }
        }
        else
        {
            cout<<"flagging coordinate = "<<newhighx<<" , "<<newhighy<<"\n";
            board[newhighx][newhighy]->flag='!';
            if(bomb==0)
            {
                cout<<"AI Wins"<<endl;
                print();
                exit(0);
            }
        }
        print();
        aiflagcheck();
    }
    aiobvious();
    aiscrounge(newlowx,newlowy);
    aiscan();
    aithink();
}



void aisolver()
{
    aiopen();
    aiobvious();
    aiscan();
    aithink();
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
		aistop=0;
		cout<<"open(1) || flag(2) || cheat(3) || solver(4)?\n";
		cin>>choice;
		while(aistop==0)
        {
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
                case 4:
                    aisolver();
                    break;
            }
        }
	}
	cout<<"you won";
}
