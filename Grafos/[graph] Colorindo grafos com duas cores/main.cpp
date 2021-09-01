#include <iostream>
#include <queue> 
#include <stdio.h> 
#include <string.h>
#include <fstream>
#include <sstream>
#include "grafo.h"
using namespace std; 

int main(){  	
	
  	int x, y;
  	
	while (true){
    int value;
	cin >> value;
	if(value == 0) return 0;
    Graph g(value); //Criando o Grafo
	do{
    	cin >> x;
    	cin >> y;
    	g.addEdge(x, y);
	}while(x != 0 || y != 0);//verifica se a lista de arestas chegou ao fim.	
	
	if(g.isBipartite() == false){
		cout << "NAO" << endl;
	}
  } 
}