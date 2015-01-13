#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <strings.h>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <math.h>
using namespace std ;


#define rows 5
#define cols 7
#define blocks 4
#define pb push_back
#define mk make_pair

#define north 0
#define east 1
#define south 2
#define west 3 

#define start_x 4   //(rows - 1)
#define start_y 0  /*
BFS : block detection is fast for randomized case :: a lot of backtracing
DFS : time consuming for block detection :: no backtracing
*/

/*
Should we also update the direction :
North , South , East , West 
*/
int bot_direction = north ;
int bot_x,bot_y ;
vector < pair< int , pair<int , int > > > blockDetails ;    //contains array of { height , pos_x , pos_y}
bool isSafe(int row, int col, int **grid){
	// n denotes the grid size

	if((row>=0)&&(row<rows)&&(col>=0)&&(col<cols)&&(grid[row][col]==-1))
		return true ;
	else
		return false ;
}

int updateDirection(int i , int j) {
int direction ;
switch(i) 
{
    case -1 : 
     direction = north ;break;
    case 0 : 
    switch(j)
    {
      case -1 :
      direction = west ;break;
      case 1 : 
      direction = east ;break;
    }
    break;
    case 1 :
      direction = south ; 
 return direction ;
}

}
bool gotonode(int pos_x , int pos_y) {
  /*
   returns true if it reaches that particular node 
   motion is as such it senses and move ....
   as it moves if block is detected it stops and returns false
  */
   int relative_x = pos_x - bot_x ;
   int relative_y = pos_y - bot_y ;
   int finalDirection = updateDirection(relative_x,relative_y);
   /*
   upon manipulating finalDirection and current direction we can give left right straight back
   or combination of above velocities
   */

   //after writing all the code 
   bot_direction = finalDirection ;
   return true ;
} 
float updateHeight() {
  /*
  returns the height by manipulating sensor data 
  */
}

void backTrack() {
  /*
  here as DFS is being used thus we can simply give a back velocity 
  it stops until it finds the back node
  */
}
void blockSearch(int **grid )    //searches for the block
{
  int blockCounter = 0 ; 
  stack < pair <int , int > > doubtPoints ;
  pair< int , int > point ,searchPoint ;
  doubtPoints.push(mk(bot_x,bot_y)) ;
  int height ;
 // cout<<doubtPoints.top().first<<endl;
  while(/*(blockCounter!=blocks)||*/(doubtPoints.size()!=0)) //second case for safety can be ignored
  { 
       point = doubtPoints.top() ;
       doubtPoints.pop();
  	for(int i = -1 ; i<=1 ;i++) {
  		for(int j = -1;j<=1;j++) {
           if(i*j==0&&i+j!=0) {
           	searchPoint = mk(point.first+i,point.second+j);
           	if(isSafe(searchPoint.first,searchPoint.second,grid)) {
           		  if(!gotonode(searchPoint.first,searchPoint.second))   //after going to that particular node true value is being returned
           	    {
                 //works if it doesn't reaches the node
                 height = updateHeight();
                 blockDetails[blockCounter].first = height ;
                 blockDetails[blockCounter].second.first =   searchPoint.first ;
                 blockDetails[blockCounter].second.second =  searchPoint.second ;
                 blockCounter++;
                 grid[searchPoint.first][searchPoint.second]=1; 
           	     backTrack();
                 //back back to the last node and continue and update the bot position  	
           	    }
                else {
                 grid[searchPoint.first][searchPoint.second] = 0 ;
                // backTrack();
                 doubtPoints.push(searchPoint);
                 bot_x = searchPoint.first ; bot_y = searchPoint.second ;
                 cout<<bot_x<<" "<<bot_y<<endl;
                //update bot position also 
                }
           	  }
           }
           if(blockCounter==blocks) return ;
  		}
  	}
  }

}
int main() //main

{  
  /*
   grid value is -1 : unvisited ; 0 : no block ; 1 : block
  */
  bot_x = start_x ; bot_y = start_y ;
  int **grid;
  grid=(int **)malloc(sizeof(int *)*(rows+1));

	for(int i=0 ; i< rows ; i++){
			grid[i]=(int *)malloc(sizeof(int)*(cols+1));
		for(int j=0 ; j<cols ; j++)
			grid[i][j]=-1;          //initializes the grid with -1 (unvisited)
	}
  grid[start_x][start_y] = 0 ;
  cout<<bot_x<<" "<<bot_y<<endl;
 // cout<<rows<<" "<<cols<<" ::: "<<start_x<<" "<<start_y<<endl;
  blockSearch(grid);
  return 0 ;
}