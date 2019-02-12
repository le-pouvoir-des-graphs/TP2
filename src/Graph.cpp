
#include <iostream>
using namespace std;

class Graph
{
	int size;
	int ** graph;

	public :

		Graph ( int x )
		{
			size = x ;
			graph = new int * [x];

			for(int i = 0; i < x; ++i)
				graph[i] = new int[x];
		}

		void init()
		{
			for ( int i = 0 ; i < size ; i ++)
			{
				for ( int j = 0 ; j < size ; j ++)
				{
					graph[i][j]= (j+i*size)+1; 				// Evite un compteur et rempli => 1, 2, 3, ...
				}

			}
		}

		int getSize()
		{
			return size;
		}

		int ** getGraph()
		{
			return graph;
		}

		void display()
		{
			for ( int i = 0 ; i < size ; i ++)
			{
				for ( int j = 0 ; j < size ; j ++)
				{
					cout << graph[i][j] << " " ;
				}
				cout << endl ;
			}
		}

		void setIJ(int i , int j , int value )
		{
			graph[i][j] = value;
		}

		int * mooreDjikstra()
		{

		}
};

/*
	matrix[0][0]=0;
	matrix[0][1]=1;
	matrix[0][2]=2;

	matrix[1][0]=3;
	matrix[1][1]=4;
	matrix[1][2]=5;

	matrix[2][0]=6;
	matrix[2][1]=7;
	matrix[2][2]=8;
*/

