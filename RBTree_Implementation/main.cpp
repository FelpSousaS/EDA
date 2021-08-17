#include <iostream>
#include <string>
#include <stdlib.h>
#include "item.h"
#include "node.h"
#include "RBTree.h"
#include "RBTree.cpp"
using namespace std;
using std :: cout;
using std :: endl;

int main(int argc, char** argv){
    
    RBTree rb;
    int op = 0, alt, buscar, chave, chave2;
    string v1, v2;
    

    while(op != 7){
        cout<< "----------------------------------" << endl ;
		cout<< "Red-Black Tree Implementation" << endl;
        cout<< "----------------------------------" << endl ;
        cout<< endl;
		cout<< "---------------MENU---------------" << endl;
        cout<< endl; 
		cout<< "1. Inserir elemento." << endl;
		cout<< "2. Remover elemento." << endl;
		cout<< "3. Remover todos os elementos." << endl;
		cout<< "4. Percurso em pre-ordem." << endl;
		cout<< "5. Buscar elemento na arvore." << endl;
		cout<< "6. Calcular a altura da arvore." << endl; 
		cout<< "7. Sair" << endl;
        cout<< endl;
		
        cout<< "Informe a operacao que deseja realizar: ";
		cin >> op;
        cout<< endl;

        switch (op){
            case 1: cout << "Insira o valor da chave: "<< endl;
                    cin>>chave;
                    cout<< endl;
                    cout<< "Digite o valor a ser inserido: "<< endl;
                    cin>>v1;
                    cout<< endl;
                    rb.insert(chave, v1);
                    cout<<"Node inserido com sucesso!"<< endl;
			        cout<< endl;
            break;
        
            case 2: cout << "Informe o valaor da chave que deseja remover: ";
                    cout<< endl;
			        cin >> chave2;
                    cout<< endl;
			        rb.remove(chave2);
			        cout << "Valor removido com sucesso!" << endl;
                    cout<< endl;
			break;

            case 3: rb.delete_allPublic();
                    cout<<"Todos os elementos foram removidos!";
			        cout<< endl;
            break;

            case 4: cout<<"Percurso em pre-ordem: "<<endl;
                    rb.RBpreorderA();
                    cout<< endl;
            break; 

            case 5: cout << "Digite a posicao que deseja encontrar: ";
			        cin >> buscar;
			        cout << "Digite o valor: ";
			        cin >> v2;
			        if(rb.search(buscar, v2)) cout<< "O valor foi encontrado com sucesso!" << endl;
			        else cout << "Valor nao encontrado" << endl;
            break;

            case 6: alt = rb.Height1();
                    cout<< "A altura da arvore e: "<< alt << endl;
            break;

            case 7: exit(0);                            
        
            default: cout<<"Operacao Invalida!"<< endl;
    
        }
    }
    return 0;
}
