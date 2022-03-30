#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Stack.cpp"
#include "randgen.h"
using namespace std;

struct walls{
	
	int l_w;
	int r_w;
	int u_w;
	int d_w;
	int isVisited;
	int x , y;
	walls()
		: l_w(1),r_w(1),u_w(1),d_w(1),isVisited(0),x(0),y(0)
	{
	};
	
};


void PrintStack(Stack<walls> & s,int arr,int entx,int enty,int endx,int endy)
{
    string filename="maze_";
	stringstream fname;
	fname<<filename<<arr<<"_path_"<<entx<<"_"<<enty<<"_"<<endx<<"_"<<endy<<".txt";
	ofstream file;
	file.open(fname.str());
	Stack<walls> temp;
    while (s.isEmpty() == false)
    {
        temp.push(s.top());
        s.pop();
    }  
 
    while (temp.isEmpty() == false)
    {
        walls t = temp.top();
        file << t.x << " "<<t.y<<endl;
        temp.pop();
 
        
        
    }
	
	
	file.close();
}

int main(){
int k_maze,m_row,n_col;
cout << "Enter the number of mazes: " ;
cin >> k_maze;
cout<< "Enter the number of rows and columns (M and N): ";
cin >>m_row>>n_col;
walls ** tempmaze;
walls ** maze;
walls *** mazearray = new walls **[k_maze] ;
for (int i = 1; i <= k_maze; i++)
{
	
	Stack<walls> maze_gen;
	walls cell;
	string filename="maze_";
	stringstream fname;
	fname<<filename<<i<<".txt";
	//filename = matrix_i.txt
	ofstream file;
	file.open(fname.str());
	file << m_row<<" "<<n_col<<endl;
    maze = new walls * [m_row];
    for (int i = 0; i<m_row; i++)
        maze[i] = new walls[n_col];
	
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			maze[i][j]=cell;
			maze[i][j].y=i;
			maze[i][j].x=j;
		}
	}
	// all cells are created l=1 r=1 u=1 d=1 isVisited=0
	int a=0;
	int b=0;
	
	while ((m_row*n_col)-1>=a)
	{
		if (b==1)
		{
			maze = new walls * [m_row];
    for (int i = 0; i<m_row; i++)
        maze[i] = new walls[n_col];
	
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			maze[i][j]=cell;
			maze[i][j].y=i;
			maze[i][j].x=j;
		}
	}
			maze_gen.push(maze[0][0]);
			maze[0][0].isVisited=1;
		}
		

		vector<int> direction;
		/*maze_gen.top().x+1<n_col&&maze_gen.top().y+1<m_row&&maze_gen.top().x-1>0&&maze_gen.top().y-1>0*/
		walls temp;
		if (b==0)
		{
			maze_gen.push(maze[0][0]);
			maze[0][0].isVisited=1;
		}
		temp = maze_gen.top();
		if (temp.x+1<n_col&& maze[temp.y][temp.x+1].isVisited==0) //right
		{
		  
		  direction.push_back(1);
		}
		if (temp.y+1<m_row&& maze[temp.y+1][temp.x].isVisited==0) // up
		{
			
			direction.push_back(2);
		}
		if (temp.x-1>=0&& maze[temp.y][temp.x-1].isVisited==0) //left
		{
			
			direction.push_back(3);
		}
		if (temp.y-1>=0&& maze[temp.y-1][temp.x].isVisited==0) //down
		{
			
		    direction.push_back(4);
		}
		
		RandGen random;
	    int size = direction.size();
		if (size==0)
		{
			maze_gen.pop();
			
		}
		else
		{
			int rand = random.RandInt(size);
			if (direction[rand]==1)
		{
			maze[temp.y][temp.x].r_w = 0;
            maze[temp.y][temp.x+1].l_w = 0;
			maze[temp.y][temp.x+1].isVisited=1;
			maze_gen.pop();
			maze_gen.push(maze[temp.y][temp.x]);
			maze_gen.push(maze[temp.y][temp.x+1]);
			
		}
		if (direction[rand]==2)
		{		
			maze[temp.y+1][temp.x].isVisited=1;
			maze[temp.y][temp.x].u_w = 0;
            maze[temp.y+1][temp.x].d_w = 0;
			maze_gen.pop();
			maze_gen.push(maze[temp.y][temp.x]);
			maze_gen.push(maze[temp.y+1][temp.x]);
		}
		if (direction[rand]==3)
		{		
			maze[temp.y][temp.x-1].isVisited=1;
			maze[temp.y][temp.x].l_w = 0;
            maze[temp.y][temp.x-1].r_w = 0;
			maze_gen.pop();
			maze_gen.push(maze[temp.y][temp.x]);
			maze_gen.push(maze[temp.y][temp.x-1]);
		}
		if (direction[rand]==4)
		{
			maze[temp.y-1][temp.x].isVisited=1;
			maze[temp.y][temp.x].d_w = 0;
            maze[temp.y-1][temp.x].u_w = 0;
			maze_gen.pop();
			maze_gen.push(maze[temp.y][temp.x]);
			maze_gen.push(maze[temp.y-1][temp.x]);
		}
		a++;
		b+=2;

		if ((m_row*n_col)-1==a)
			{
			for (int i = 0; i < m_row; i++)
			{
			for (int j = 0; j < n_col; j++)
				{
				file << "x="<<maze[i][j].x<<" y="<<maze[i][j].y<<" l="<<maze[i][j].l_w<<" r="<<maze[i][j].r_w<<" u="<<maze[i][j].u_w<<" d="<<maze[i][j].d_w<<endl;
				}
			}	
			tempmaze=maze;
			mazearray[i-1]=tempmaze;
		
			maze_gen.makeEmpty();
			b=1;


			/*for (int i = 0; i < m_row; i++) {
         delete [] maze[i];
           
       }
       delete [] maze;*/
	  
	  
	   file.close();
			}
		}
		
		
		
	}	
	
	
	
	
	
	
	  
}
cout<<"All mazes are generated.\n";
cout << "Enter a maze ID between 1 to 5 inclusive to find a path: ";
int arr,entx,enty,endx,endy;
cin >> arr;
cout<<"Enter x and y coordinates of the entry points (x,y) or (column,row): ";
cin>>entx>>enty;
cout<<"Enter x and y coordinates of the exit points (x,y) or (column,row): ";
cin>>endx>>endy;
Stack<walls> path;
walls  temp;
path.push(mazearray[arr-1][enty][entx]);
walls ** p_maze=mazearray[arr-1];
while (true)
{
vector<int> direction;
		
		
		temp = path.top();
		if (temp.r_w==0&&p_maze[temp.y][temp.x+1].isVisited==1) //right
		{
		  
		  direction.push_back(1);
		}
		if (temp.u_w==0&&p_maze[temp.y+1][temp.x].isVisited==1) // up
		{
			
			direction.push_back(2);
		}
		if (temp.l_w==0&&p_maze[temp.y][temp.x-1].isVisited==1) //left
		{
			
			direction.push_back(3);
		}
		if (temp.d_w==0&&p_maze[temp.y-1][temp.x].isVisited==1) //down
		{
			
		    direction.push_back(4);
		}
		
		RandGen random;
	    int size = direction.size();
		if (size==0)
		{
			path.pop();
			
		}
		else
		{
			int rand = random.RandInt(size);
			if (direction[rand]==1)
		{
			
			
			p_maze[temp.y][temp.x+1].isVisited=0;
			p_maze[temp.y][temp.x].isVisited=0;
			path.push(p_maze[temp.y][temp.x+1]);
			
			
		}
		if (direction[rand]==2)
		{		
			
			p_maze[temp.y+1][temp.x].isVisited=0;
			p_maze[temp.y][temp.x].isVisited=0;
			path.push(p_maze[temp.y+1][temp.x]);
		}
		if (direction[rand]==3)
		{		
			
			p_maze[temp.y][temp.x-1].isVisited=0;
			p_maze[temp.y][temp.x].isVisited=0;
			path.push(p_maze[temp.y][temp.x-1]);
		}
		if (direction[rand]==4)
		{
			
			p_maze[temp.y-1][temp.x].isVisited=0;
			p_maze[temp.y][temp.x].isVisited=0;
			path.push(p_maze[temp.y-1][temp.x]);
		}

		if (path.top().x==endx && path.top().y==endy)
			{
			PrintStack(path,arr,entx,enty,endx,endy);
			
			break;

			}
			
		}

		
		
		
	
}

return 0;
}
//for (int i = 0; i < m_row; i++) {
//        delete [] maze[i];
//        
//    }
//    delete [] maze;


