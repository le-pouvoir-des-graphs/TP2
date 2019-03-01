#include <iostream>
#include "Graph.cpp"

using namespace std;


int main()
{

	Graph * mDjikstra = new Graph (7);
	mDjikstra->hardCodedInit();
	mDjikstra->mooreDijkstra(0);
	// cout << " \n Avec HEAP : " << endl ;
	// mDjikstra->mooreDijkstraHeap(0);
	cout << " \n Graphe : " << endl ;
	mDjikstra->display();




	return(1);
}
