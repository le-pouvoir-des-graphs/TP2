
#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>

using namespace std;


struct Noeud 
{
	int pos;
	int value;
};

struct Comparaison
{
	bool operator()(const Noeud & i, const Noeud & j)
	{
		return( i.value > j.value ); 
	}
};

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

		void hardCodedInit()
		{ 
			size = 7;
			int graphBis[size][size] = {	
											{0,1,2,0,0,0,0},
											{1,0,2,2,0,3,0},
											{2,0,0,3,4,0,0},
											{0,2,3,0,2,3,3},
											{0,0,4,2,0,0,5},
											{0,3,0,3,0,0,4},
											{0,0,0,3,5,4,0}
										};
			for ( int i = 0 ; i < size ; i ++)
			{
				for ( int j = 0 ; j < size ; j ++)
				{
					graph[i][j]= graphBis[i][j];
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

		int minDistance(int dist[], bool pccTrouve[]) 
		{
			int min = INT_MAX, min_index; 
		   
			for (int v = 0; v < size ; v++)
			{
				if (pccTrouve[v] == false && dist[v] <= min)
				{
					min = dist[v], min_index = v; 
				}
			}
			return min_index; 
		} 
		   
		// Affiche les resultats
		int display_shortest_paths (int dist[], int src , int pere[] ) 
		{
			for (int i = 0; i < size ; i++)
			{
				printf(" - Atteindre le sommet %d depuis le sommet %d coutera au minimum : %d \n", i, src, dist[i]); 
				//printf(" Le sommet pere de %d est %d\n", i , pere[i]  );
				cout << " 	Plus court chemin : " ;
				int tmp = i ;
				while ( tmp != src )
				{
					cout << tmp << " <- "; 
					tmp = pere[tmp];
				}
				cout << src << endl;
				
			}
		} 
		   
		// mooreDijkstra  algo  
		int * mooreDijkstra (int src) 
		{ 
			int dist[size];       // Valeur des chemins les plus courts du sommet source jusqu'a tous les autres sommets    
			bool pccTrouve[size]; // pccTrouve[i] Vrai si le plus court chemin est trouvé
			int * pere = new int[size];

		   
			// Initialisation des valeurs
			for (int i = 0; i < size ; i++) 
				dist[i] = INT_MAX, pccTrouve[i] = false; 

			dist[src] = 0;      // la distance d'un point a lui même est toujours 0
			pere[0] = -1;       // Le sommet est son propre pere car il est le point de départ du chemin
		   
			 // Trouve le pcc pour tous les sommets
			for (int count = 0; count < size -1; count++) 
			{ 
				int u = minDistance(dist, pccTrouve); 
				pccTrouve[u] = true; 
				// Mise a jour de la distance des sommets adjacent au sommet courant 
				for (int v = 0; v < size ; v++) 
				{
					if (!pccTrouve[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v] )
					{
						dist[v] = dist[u] + graph[u][v]; 
						pere[v] = u ;
					}
				}
			} 

			display_shortest_paths (dist , src , pere); 
			return pere;
		}
		
		// mooreDijkstra  algo  
		int * mooreDijkstraHeap (int src) 
		{ 
			vector<Noeud> d ;
			bool pccTrouve[size];
			int dist[size]; 
			int * pere = new int[size];

			
			// Initialisation des valeurs
			for (int i = 0; i < size ; i++) 
				dist[i] = INT_MAX, pccTrouve[i] = false; 

			dist[src] = 0;      // la distance d'un point a lui même est toujours 0
			pere[0] = -1;       // Le sommet est son propre pere car il est le point de départ du chemin
			
			d.push_back(Noeud());
			d.back().value = 0;
			d.back().pos = src;
			make_heap(d.begin(),d.end(),Comparaison());
			pop_heap(d.begin(),d.end(),Comparaison());
			int u = d.back().pos ;
			int valueU = d.back().value ;
			for (int count = 0; count < size -1; count++) 
			{ 
				pccTrouve[u] = true; 
				// Mise a jour de la distance des sommets adjacent au sommet courant 
				for (int v = 0; v < size ; v++) 
				{
					if (! pccTrouve[v] && graph[u][v] && valueU != INT_MAX && valueU + graph[u][v] < dist[v] )
					{
						d.push_back(Noeud());
						d.back().value = valueU + graph[u][v];
						d.back().pos = u ;
						dist[v] = valueU + graph[u][v]; 
						pere[v] = u ;
						push_heap(d.begin(),d.end(),Comparaison());
					}
				}
				pop_heap(d.begin(),d.end(),Comparaison());
				u = d.back().pos ;
				valueU = d.back().value ;
			} 

			display_shortest_paths (dist , src , pere); 
			return pere;
		}
};

