#ifndef DS_H_2021
#define DS_H_2021
#include <iostream>
#include <unordered_map>
using namespace std;

struct Representative;

struct Node {
    int element; // guarda o valor do elemento
    Node *next; // ponteiro para o proximo node na lista
    Representative *repr; // ponteiro para o representante
};

struct Representative {
    Node *head; // ponteiro para o primeiro node na lista
    Node *tail; // ponteiro para o ultimo node da lista
    int size; // numero de elementos na lista
};

// Classe que implementa conjuntos disjuntos usando 
// listas encadeadas e heuristica de uniao ponderada
class DisjointSets {
private:
    std::unordered_map<int, Node*> nodeAddress; // tabela hash
    
public:
    // funcao Make-Set
    // cria um conjunto somente com o elemento 'elem' do tipo int.
    // Um conjunto eh composto por um objeto Representative e um objeto Node.
    // Um par (elem, Node*) deve ser armazenado na tabela hash 'nodeAddress'
    void makeset(const int& elem); 

    // funcao Find
    // Devolve um ponteiro para o representante de 'elem'
    // A fim de encontrar o Node que contem 'elem', deve ser usada a tabela hash 'nodeAddress'
    Representative* find(const int& elem);

    // funcao Union
    // Se 'elem1' e 'elem2' nao estiverem no mesmo conjunto,
    // entao os seus conjuntos serao unidos. Eles terao um mesmo representante.
    // Supoe que esta funcao eh sempre chamada para dois elementos em conjuntos disjuntos
    // Um dos Representative não será mais usado e deve ser deletado
    void unionSets(const int& elem1, const int& elem2);
    
    // funcao printSet
    // imprime na tela todos os elementos que estao no mesmo conjunto que 'elem'
    // no formato: { e1 e2 e3 ... en }
    // onde cada elemento eh separado por espacos em branco
    void printSet(const int& elem);
    
    // Destrutor
    ~DisjointSets() {
        // percorre todos os elementos da tabela hash e libera todos os 
        // elementos do tipo Node que foram alocados dinamicamente.
        // A tabela hash em si nao precisa ser liberada ja que ela foi 
        // alocada estaticamente pelo proprio compilador. Ele se encarrega de libera-la.
        // Note que essa implementacao tem um problema pois os elementos do tipo
        // Representative nao sao liberados aqui no destrutor. Isso deve ser consertado futuramente.
        // Voce consegue visualizar alguma solucao?
        for(auto it = nodeAddress.begin(); it != nodeAddress.end(); ++it) {
            delete it->second;
        }
    }
};

void DisjointSets :: makeset(const int& elem){
    // Create a new Set
    Representative *rep = new Representative;
  
    // Create a new linked list node
    // to store given key
    rep->head = new Node;
  
    // Initialize head and tail
    rep->tail = rep->head;
    nodeAddress[elem] = rep->head;
  
    // Create a new set
    rep->head->element = elem;
    rep->head->repr = rep;
    rep->head->next = nullptr;
}

Representative* DisjointSets :: find(const int& elem){
    Node *aux = nodeAddress[elem];
    return (aux->repr);
}

void DisjointSets :: unionSets(const int& elem1, const int& elem2){
    Representative *rep1 = find(elem1);
    Representative *rep2 = find(elem2);

    Node *aux;
    
    if(elem2 > elem1){
        aux = rep2->head;
        
        while(aux != 0){
            aux->repr = rep1;
            aux = aux->next;
        }

        (rep1->tail)->next = rep2->head;
        rep1->tail = rep2->tail;

        delete rep2;
    }else{
        aux = rep1->head;

        while(aux != 0){
            aux->repr = rep2;
            aux = aux->next;
        }

        (rep2->tail)->next = rep1->head;
        rep2->tail = rep1->tail;

        delete rep1;
    }
}

void DisjointSets :: printSet(const int& elem){
    Representative *rep = find(elem);
    Node *aux = rep->head;

    cout << "{ ";
    
    while(aux != 0){
        cout << aux->element << " ";
        aux = aux->next;
    }

    cout << " }";
}




#endif