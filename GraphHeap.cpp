#include <iostream>
#include <string>
#include <limits.h> 
#include <stdio.h> 
#include <vector>
#include <algorithm>

using namespace std;

int e[7] = {0,1000,1000,1000,1000,1000,1000};

void display_shortest_path(int taille, int pere[], int d[]) {
	int p[taille];
	int poids[taille];
	int cpt = taille-1;
	int beau_poid[taille];
	int lol = taille;
		for ( int jj =  0 ; jj < taille ; jj++ )
		{
			beau_poid [jj] = poids[lol--];
		}
	
	while (cpt>0) 
	{
		int j =0;
		int i = cpt;
		while(d[i]>0) {
			p[j]=i+1;
			poids[j]=d[i];
			j++;
			i=pere[i]-1;
		}
		p[j]=1;
		poids[j]=0;
		printf(" - Atteindre le sommet %d depuis le sommet %d coutera au minimum : %d \n",p[0]-1,p[j]-1, poids[i]);
		cout << " 	Plus court chemin : " ;
		for(int k=j;k>=0;k--) {
			if(k!=0) {
				cout<< p[k]-1<<" -> ";
			}
			else {
				cout << p[k]-1;
			}
		}
		cout<<endl;
		cpt--;
	}
}

bool cmp(const int & i, const int & j)
{
	return(e[i] > e[j]); 
}

void display(vector<int> & v)
{
	int n = v.size();

	for(int i = 0; i < (n-1); i++)
		cout << v[i] << " - ";

	cout << v[n-1] << endl;
}

void MooreDijkstra(int s[7][7],int taille) {
	vector<int> v;
	for(int i=0;i<taille;i++) {
		v.push_back(i);
	}
	make_heap(v.begin(),v.end(),cmp);
	pop_heap(v.begin(),v.end(),cmp);
	v.back();
	v.pop_back();
	int d[taille] = {0,1000,1000,1000,1000,1000,1000};
	bool c[taille] = {true,false,false,false,false,false,false};
	int pere[taille] = {0,0,0,0,0,0,0};
	int j=0;
	for(int k=1;k<taille;k++) {
		for(int i=0;i<taille;i++) {
			if(c[i]==false && d[j]+s[j][i]<=d[i]) {
				d[i]=d[j]+s[j][i];
				e[i]=e[j]+s[j][i];
				pere[i]=j+1;
			}
		}
		make_heap(v.begin(),v.end(),cmp);
		pop_heap(v.begin(),v.end(),cmp);
		v.back();
		j=v.back();
		v.pop_back();
		c[j]=true;
	}
	display_shortest_path(taille,pere,d);
}
		
int main() {
	int x=7;
	int s[7][7] = { {99 ,1,2,99,99,99,99},
					{1,99,2,2,99,3,99},
					{2,99,99,3,4,99,99},
					{99,2,3,99,2,3,3},
					{99,99,4,2,99,99,5},
					{99,3,99,3,99,99,4},
					{99,99,99,3,5,4,99}
				};
	MooreDijkstra(s,x);
	return 0;
}
