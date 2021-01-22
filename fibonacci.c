#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "lib.h"
#define SIZE 4
int score=0;
int arr[]={1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765};
int search(int a,int b)
{	
	int i;
	if(a==1&&b==1)
		return 1;
	else
	{
		for(i=0;i<17;i++)
		if(arr[i]==a)
			break;
		return(arr[i+1]==b||arr[i-1]==b);
	}
}
void display(int board[SIZE][SIZE],int m)
{	
	printf("\033[2J");	
	printf("\n\n\n\n\n\n\n\n\n                                                                          BEST SCORE:%d\n                                                                                YOUR SCORE:%d\n\n",m,score);
	for(int i=0;i<SIZE;i++)
	{printf("                                             ");
		for(int j=0;j<SIZE;j++)
		{	if(board[i][j]==0)
				printf(".   ");
			else
			{
				printf("\033[%dm",color(board[i][j]));
				if(board[i][j]<10)
					printf("%d   ",board[i][j]);
				else
					printf("%d  ",board[i][j]);
				printf("\033[37m");
			}
		}
		printf("\n\n");
										}
}
int find(int array[SIZE],int x,int stop) 
{
		int t;
		if (x==0) 
		{
			return x;
		}							
		for(t=x-1;t>=0;t--) 
		{
			if (array[t]!=0) 
			{
				if(search(array[t],array[x]))
				{
					return t;
				}
				return t+1;
			} 
			else 
			{
				if (t==stop) 
				{
					return t;
				}
			}
		}
		return x;
}
bool movearray(int array[SIZE]) 
{
	bool success = false;
	int x,t,stop=0;
	for (x=0;x<SIZE;x++) 
	{
		if (array[x]!=0) 
		{
			t = find(array,x,stop);
			if (t!=x) 
			{
				if (array[t]==0) 
				{
					array[t]=array[x];
				}
				else if (search(array[t],array[x])) 
				{
					array[t]=array[t]+array[x];
					score+=array[t];
					stop = t+1;
				}
				array[x]=0;
				success = true;
																													   }
																
		}
	}
	return success;
}
void rotate(int board[SIZE][SIZE]) 
{
	int i,j,n=SIZE;
	int tmp;
	for (i=0; i<n/2; i++) 
	{
		for (j=i; j<n-i-1; j++) 
		{
			tmp = board[i][j];
			board[i][j] = board[j][n-i-1];
			board[j][n-i-1] = board[n-i-1][n-j-1];
			board[n-i-1][n-j-1] = board[n-j-1][i];
			board[n-j-1][i] = tmp;
		}
	}
}
bool moveleft(int board[SIZE][SIZE]) 
{
	bool success = false;
	int x;
	for (x=0;x<SIZE;x++) 
	{
		success=success|movearray(board[x]);
	}
	return success;
}
bool moveup(int board[SIZE][SIZE]) 
{
	bool success;
	rotate(board);
	success = moveleft(board);
	rotate(board);
	rotate(board);
	rotate(board);
	return success;
}
bool moveright(int board[SIZE][SIZE]) 
{
	bool success;
	rotate(board);
	rotate(board);
	success = moveleft(board);
	rotate(board);
	rotate(board);
	return success;
}
bool movedown(int board[SIZE][SIZE]) 
{
	bool success;
	rotate(board);
	rotate(board);
	rotate(board);
	success = moveleft(board);
	rotate(board);
	return success;
}
void addrandom(int board[SIZE][SIZE]) 
{
	int x,y;
	srand(time(NULL));
	do
	{
		x=rand()%4;                                                                                                                                                         
		y=rand()%4;
	}
	while(board[x][y]);
	board[x][y]=1;
}
void create(int board[SIZE][SIZE]) 
{		score=0;
		int x,y;
		for (x=0;x<SIZE;x++) 
		{
						
			for (y=0;y<SIZE;y++) 
			{
				board[x][y]=0;
			}
		}
		addrandom(board);
	//	display(board,m);
		score = 0;
}
bool findpair(int board[SIZE][SIZE]) 
{
	bool success = false;
	int x,y;
	for (x=0;x<SIZE;x++) 
	{
		for (y=0;y<SIZE-1;y++) 
		{
			if (search(board[x][y],board[x][y+1])) 
				return true;
		}
	}
	return success;
}

int countempty(int board[SIZE][SIZE]) 
{
	int x,y;
	int count=0;
	for (x=0;x<SIZE;x++) 
	{
		for (y=0;y<SIZE;y++) 
		{
			if (board[x][y]==0) 
			{
				count++;
			}
		}
	}
	return count;
}

bool gameover(int board[SIZE][SIZE]) 
{
	bool ended = true;
	if (countempty(board)>0) 
		return false;
	if (findpair(board)) 
		return false;
	rotate(board);
	if (findpair(board)) 
		ended = false;
	rotate(board);
	rotate(board);
	rotate(board);
	return ended;
}
int main() 
{
	int board[SIZE][SIZE];
	char c,n;
	int m,k;
	bool success;
	FILE *hs;
	hs=fopen("highscore.txt","r+");
	fscanf(hs,"%d",&m);
	printf("\033[2J");
	printf("\033[?25l");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                               i-instructions\n                                            any other key to play\n\n\n");
	scanf("%c",&c);
	if(c=='i')
	{
			 printf("\033[2J");
			 printf("\n*fibinnocci series(sum of previous two numbers):1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584...\nnumbers can be added only when they are in series\n*while playing game:\n  -use a,s,w,d to move\n  -q to exit\n  -i for information\n  -r to restart");
			 printf("\n\nenter any key to continue:");
			 scanf(" %c",&n);
	}
	create(board);
	display(board,m);
	while (true) 
	{
		scanf(" %c",&c);
		switch(c) 
		{	
			case 'a':
			case 'A':success = moveleft(board);  break;
	 		case 'd':			 
			case 'D':success = moveright(board); break;
			case 'w':
			case 'W':success = moveup(board);    break;
			case 's':
			case 'S':success = movedown(board);  break;
			default: success = false;
		}
		if (success) 
		{	
			addrandom(board);
			display(board,m);
			if (gameover(board)) 
			{
				break;
			}
		}
		if(c=='i'||c=='I')
			 printf("\n*fibinnocci series(sum of previous two numbers):1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584...\nnumbers can be added only when they are in series\n*while playing game:\n  -use a,s,w,d to move\n  -q to exit\n  -i for information\n  -r to restart\n");
		
		if (c=='q' || c=='Q') 
		{
			printf("        QUIT? (y/n)         \n");
			scanf(" %c",&c);
			if (c=='y'||c=='Y') 
			{
				break;
			}
			display(board,m);
																												   }
		if (c=='r'||c=='R') 
		{
			printf("       RESTART? (y/n)       \n");
			scanf(" %c",&c);
			if (c=='y'||c=='Y') 
			{
				create(board);
				display(board,m);
			}
		 }
	}
	if(m<=score)
	{	rewind(hs);
		fprintf(hs,"%d",score);
		m=score;
	}
	printf("\033[2J");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                 GAME OVER\n                                                 YOUR SCORE:%d\n                                                 BEST SCORE:%d          \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",score,m);
	return 0;
}
