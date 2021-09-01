#include <iostream>
#include <queue> 
#include <stdio.h> 
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std; 


class Graph { 
private: 
    // numero de vertices 
    int num_vert; 
  
    // matriz de adjacencia
	int **matriz; 
  
public: 
	
    // construtor 
    Graph(int x){ 
        num_vert = x; 
  
        //construtir matriz adjacencia e inicializar todos os elementos com 0
		matriz = new int*[num_vert];
		for (int i = 0; i < num_vert; ++i)
   	    matriz[i] = new int[num_vert];
   	
        for (int i = 0; i < num_vert; ++i) { 
            for (int j = 0; j < num_vert; ++j) { 
                matriz[i][j] = 0; 
            } 
        } 
    }
	~Graph(){
		for (int i = 0; i < num_vert; ++i)
    		delete [] matriz[i];
			delete [] matriz;
	} 
  
    void addEdge(int x, int y){ 
        // verifica se o vértice está conectado a si mesmo
        if (x == y) { 
        } 
        else { 
            // liga os vertices 
            matriz[y][x] = 1; 
            matriz[x][y] = 1; 
        } 
    }
	
	bool isBipartite(){
		int *cor = new int[num_vert]; // vetor que guarda a cor
		int i; 
		for(int c = 0; c < num_vert; c++){
			cor[c] = 0;
		}
		cor[0] = 1;
		queue <int> number;
		number.push(0);
		
		while(!number.empty()){
			
		i = number.front(); // acessa o proximo elemento da lista
		number.pop(); // remove o proximo elemento da lista
            for (int j = 0; j < num_vert; ++j) { 
                if(matriz[i][j] == 1){
					if(cor[j] == 0){
						number.push(j);
					}
					
					if(cor[i] == 1){
						if(cor[j] == 1) return false;
						else cor[j] = 2;
					}
				
					if(cor[i] == 2){
						if(cor[j] == 2) return false;
						else cor[j] = 1;
					}
				}
            } 
        }       
        cout << "SIM" << endl;
        return true;
	} 

};