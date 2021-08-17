#include <iostream>
#include "bnode.h"
using namespace std;

class Btree {
private:

    Bnode *root; 
    // grau minimo do no
    int d; 
protected:
    // libera todos os nos e deixa arvore vazia
    Bnode *clear(Bnode *node);
public:
    // Construtor
    Btree(int d);
    // Destrutor
    ~Btree();
    // Insere uma chave na arvore 
    void insert(int k);
    // Busca uma chave k na arvore
    bool search(int k);
    // Imprime as chaves da arvore
    void printKeys();
    
	void remove(int k);
    
    
};

Btree::Btree(int d) {
    this->d = d;
    root = null;
}

bool Btree::search(int k) {
    if(root != null) {
        int i;
        Bnode *node = root->search(k,i);
        return (node != nullptr);
    }
    else return false;
}

void Btree::insert(int k) {
    // Arvore vazia
    if(root == null) {
        root = new Bnode(d, true); // Aloca memoria
        root->key[0] = k; // Insere a chave
        root->n = 1; // Atualiza o numero de chaves
    }
    // Arvore nao-vazia
    else { 
        // Se a raiz estiver cheia
        if(root->n == 2*d-1) {
            // Aloca memoria para a nova raiz
            Bnode *s = new Bnode(d, false);
            
            // Faz a raiz antiga ser filha da nova raiz
            s->c[0] = root;

            // Divide a raiz antiga e move uma chave para a nova raiz s
            s->splitChild(0);

            // A nova raiz tem dois filhos agora. 
            // Decida qual dos dois filhos vai receber
            // a nova chave
            int i = 0;
            if(s->key[0] < k)
                i++;
            s->c[i]->insertNonFull(k);

            // Muda a raiz para s
            root = s;
        }
        else {
            root->insertNonFull(k);
        }
        
    }
}

void Btree::printKeys() {
    if(root != null)
        root->printKeys();
}

Btree::~Btree() {
    root = clear(root);
}


Bnode *Btree::clear(Bnode *node) {
    if(node != null) {
        if(node->leaf == true) {
            delete node;
            return nullptr;
        }
        else {
            for(int i = 0; i <= node->n; i++) {
                node->c[i] = clear(node->c[i]);
            }
            delete node;
            return nullptr;
        }
    }
}


