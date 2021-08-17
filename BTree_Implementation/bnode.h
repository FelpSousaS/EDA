#ifndef BNODE_H
#define BNODE_H
#include <iostream>
using namespace std;

class Bnode {
private:
    int *key;       // vetor de chaves
    int d;          // grau minimo
    Bnode **c;      // vetor de ponteiros para filhos
    int n;          // numero atual de chaves
    bool leaf;      // true se o noh eh uma folha, false caso contrario
public:
    // Construtor
    Bnode(int d, bool leaf);

    // Destrutor
    ~Bnode();

    // Funcao que busca a chave k na subarvore 
    // enraizada neste no. Se a chave existir, retorna
    // o ponteiro para o no e o valor do indice da chave
    // na variavel index. Caso contrario, retorna nullptr
    // e o valor de index eh indefinido.
    Bnode *search(int k, int& index);

    // Imprime todas as chaves do no em ordem crescente
    // Incompleto
    void printKeys();

    // Funcao que divide o filho c[i] deste no.  
    // O no apontado por c[i] deve estar cheio 
    // quando esta funcao eh chamada.
    void splitChild(int i);

    // Funcao que insere uma nova chave na subarvore 
    // enraizada neste no. Supomos que o no nao esta 
    // cheio quando esta funcao eh chamada 
    void insertNonFull(int k);

    // Faz Btree uma classe amiga desta, para que possamos acessar
    // os membros privados desta classe nas funções de Btree. 
    friend class Btree; 
    
    int findKey(int k);
    void remove(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

Bnode::Bnode(int d, bool leaf) {
    this->d = d;            // grau minimo do noh
    this->leaf = leaf;      // indica se noh eh folha
    n = 0;                  // no inicio o noh nao tem chaves
    key = new int[2*d - 1]; // o noh pode ter no maximo 2d-1 chaves
    c = new Bnode*[2*d];    // o noh pode ter no maximo 2d filhos
}

Bnode::~Bnode() {
    std::cout << "No removido com chaves: " << std::endl;
    for(int i = 0; i < n; i++) std::cout << key[i] << " ";
    std::cout << std::endl;
    delete[] key;
    delete[] c;
}


Bnode *Bnode::search(int k, int& index) {
    // Encontra a primeira chave maior ou igual a k
    int i = 0;
    while(i <= n-1 && k > key[i])
        i++;
    
    // A chave foi encontrada neste no.
    if(i <= n-1 && k == key[i]) {
        index = i;
        return this;
    }
    // A chave nao foi encontrada neste no e ele eh folha.
    else if(leaf == true)
        return null;
    // Desce para o filho apropriado
    else 
        return c[i]->search(k, index);
}

 
void Bnode::printKeys() { 
    int i;
    for(i = 1;i < n; i++){
		if(leaf == false)
			c[i]->printKeys();
		
		std::cout<< " " << key[i];
	}
    
	if(leaf == false)
		c[i]->printKeys();	
} 


void Bnode::splitChild(int i) {
    // y eh o filho deste no que sera dividido
    Bnode *y = this->c[i];

    // Aloca memoria para um novo no que armazenara as
    // d-1 maiores chaves de y
    Bnode *z = new Bnode(d, y->leaf);
    z->n = d-1;

    // Copia as ultimas d-1 chaves de y para z
    for(int j = 0; j < d-1; j++)
        z->key[j] = y->key[j+d];

    // Copia os ultimos d filhos de y para z
    if(y->leaf == false) {
        for(int j = 0; j < d; j++)
            z->c[j] = y->c[j+d];
    }

    // Atualiza o numero de chaves de y
    y->n = d-1;

    // Como este no tera um novo filho, criamos
    // espaco para o ponteiro para o novo filho
    for(int j = n; j >= i+1; j--)
        c[j+1] = c[j];

    // Faz c[i+1] apontar para z
    c[i+1] = z;

    // Move a chave mediana de y para este no.
    // Encontra a posicao da nova chave e move todas
    // as chaves maiores uma posicao para a frente
    for(int j = n-1; j >= i; j--)
        key[j+1] = key[j];

    // Copia a chave mediana de y para este no.
    key[i] = y->key[d-1];

    // Incrementa o numero de chaves deste no.
    n = n + 1;
}

void Bnode::insertNonFull(int k) {
    // Inicia i com o indice da chave mais a direita
    int i = n-1;

    // Se este no eh folha
    if(leaf == true) {
        // Este loop move as chaves uma posicao para 
        // a direita ate achar a posicao correta da nova chave.
        while(i >= 0 && k < key[i]) {
            key[i+1] = key[i];
            i--;
        }
        // Insere a nova chave na posicao correta
        key[i+1] = k;
        n = n+1;
    }
    // Se este no nao eh folha
    else {
        // Encontra o filho que tera a nova chave
        while(i >= 0 && k < key[i]) 
            i--;
        
        i++;

        // Checa se o filho encontrado esta cheio
        if(c[i]->n == 2*d-1) {
            // Se o filho c[i] deste no estiver cheio, divida-o
            splitChild(i);

            // Depois de dividir, a chave do meio de c[i] sobe
            // para este no e c[i] eh dividido  em dois. Agora,
            // devemos decidir qual das duas metades tera a 
            // nova chave
            if(k > key[i])
                i++;
        }
        c[i]->insertNonFull(k);
    }

}

int Bnode::findKey(int k){ 
	int idx=0; 
	while (idx<n && key[idx] < k) 
		++idx; 
	return idx; 
} 


void Bnode::remove(int k){ 
	int idx = findKey(k); 

	if (idx < n && key[idx] == k){ 
		if (leaf) 
			removeFromLeaf(idx); 
		else
			removeFromNonLeaf(idx); 
	} 
	else{ 

		if (leaf) 
		{ 
			cout << "A chave "<< k <<" nao existe na arvore\n"; 
			return; 
		} 

		bool flag = ( (idx==n)? true : false ); 

		if (c[idx]->n < d) fill(idx); 
 
		if (flag && idx > n) c[idx-1]->remove(k); 
		else c[idx]->remove(k); 
	} 
	return; 
} 
 
void Bnode::removeFromLeaf (int idx){ 

	
	for (int i=idx+1; i<n; ++i) 
		key[i-1] = key[i]; 
 
	n--; 

	return; 
} 
 
void Bnode::removeFromNonLeaf(int idx){ 

	int k = key[idx]; 

	if (c[idx]->n >= d){ 
		int pred = getPred(idx); 
		key[idx] = pred; 
		c[idx]->remove(pred); 
	}  
	else if (c[idx+1]->n >= d){ 
		int succ = getSucc(idx); 
		key[idx] = succ; 
		c[idx+1]->remove(succ); 
	}  
	else{ 
		merge(idx); 
		c[idx]->remove(k); 
	} 
	return; 
} 
 
int Bnode::getPred(int idx){ 
	
	Bnode *cur=c[idx]; 
	while (!cur->leaf) 
		cur = cur->c[cur->n]; 

	 
	return cur->key[cur->n-1]; 
} 

int Bnode::getSucc(int idx){ 
 
	Bnode *cur = c[idx+1]; 
	while (!cur->leaf) 
		cur = cur->c[0]; 
	
	return cur->key[0]; 
} 

void Bnode::fill(int idx){ 

	if (idx!=0 && c[idx-1]->n>=d) borrowFromPrev(idx); 

	else if (idx!=n && c[idx+1]->n>=d) borrowFromNext(idx); 


	else{ 
		if (idx != n) merge(idx); 
		else merge(idx-1); 
	} 
	return; 
} 
 
void Bnode::borrowFromPrev(int idx){ 

	Bnode *child=c[idx]; 
	Bnode *sibling=c[idx-1]; 

	for (int i=child->n-1; i>=0; --i) 
		child->key[i+1] = child->key[i]; 
 
	if (!child->leaf){ 
		for(int i=child->n; i>=0; --i) 
			child->c[i+1] = child->c[i]; 
	} 

	child->key[0] = key[idx-1]; 
 
	if(!child->leaf) child->c[0] = sibling->c[sibling->n]; 
 
	key[idx-1] = sibling->key[sibling->n-1]; 

	child->n += 1; 
	sibling->n -= 1; 

	return; 
} 


void Bnode::borrowFromNext(int idx){ 

	Bnode *child=c[idx]; 
	Bnode *sibling=c[idx+1]; 

	child->key[(child->n)] = key[idx]; 

	 
	if (!(child->leaf)) child->c[(child->n)+1] = sibling->c[0]; 
 
	key[idx] = sibling->key[0]; 
 
	for (int i=1; i<sibling->n; ++i) 
		sibling->key[i-1] = sibling->key[i]; 

	 
	if (!sibling->leaf){ 
		for(int i=1; i<=sibling->n; ++i) 
			sibling->c[i-1] = sibling->c[i]; 
	} 

	child->n += 1; 
	sibling->n -= 1; 

	return; 
} 


void Bnode::merge(int idx){ 
	Bnode *child = c[idx]; 
	Bnode *sibling = c[idx+1]; 

 
	child->key[n-1] = key[idx]; 

	 
	for (int i=0; i<sibling->n; ++i) 
		child->key[i+d] = sibling->key[i]; 

	
	if (!child->leaf){ 
		for(int i=0; i<=sibling->n; ++i) 
			child->c[i+d] = sibling->c[i]; 
	} 

	for (int i=idx+1; i<n; ++i) 
		key[i-1] = key[i]; 

	
	for (int i=idx+2; i<=n; ++i) 
		c[i-1] = c[i]; 

	
	child->n += sibling->n+1; 
	n--; 

	delete(sibling); 
	return; 
} 

#endif