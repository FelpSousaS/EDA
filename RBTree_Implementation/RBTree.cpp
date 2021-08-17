#include <iostream>
#include <stack>
#include "item.h"
#include "node.h"
#include "RBTree.h"
using std :: cout;
using std :: endl;

RBTree::RBTree(){ //Construtor
    nil = new Node{};
    nil->key = 0;
    nil->left = nil->right = nil->parent = nil;
    nil->color = BLACK;
    root = nil;
}

void RBTree :: left_rotate (Node *x) { 
	Node *y = x -> right ;
	x -> right = y -> left ;
	 
     if (y -> left != nil){
		y -> left -> parent = x;
     }   
	 
     y -> parent = x -> parent ;
	 
     if (x -> parent == nil) {
		root = y;
	 } 
	 else if (x == x -> parent -> left) {
		x -> parent -> left = y;
	 } else {
		    x -> parent -> right = y ;
	}
	y -> left = x ;
	x -> parent = y;
}

void RBTree :: right_rotate ( Node *x) { 
	 Node *y = x -> left ;
     x -> left = y -> right ;
	if (y -> right != nil ){
		y -> right -> parent = x ;
		y -> parent = x -> parent ;
	}		
	if (x -> parent == nil ){
		root = y;
    } 	
	else if (x == x -> parent -> right ){
		x -> parent -> right = y ;
	} else {
		x -> parent -> left = y;
    }
		y -> right = x;
		x -> parent = y;
}


void RBTree :: insert ( const Tkey& key , const Tvalue& value) {

Node *newNode = new Node;
	newNode -> key = key ;
	newNode -> value = value;
	newNode -> left = newNode -> right = nil ;
	newNode -> parent = nil ;
	
	RBinsert ( newNode );
}

void RBTree :: RBinsert ( Node *z ) {
	Node *father = nil;
	Node *son = root;
	while ( son != nil ) {
	    father = son;
	    if(z -> key == son -> key ) {
	        delete z; 
	        return;
        }
	    son = (z -> key < son -> key ) ? son -> left : son -> right ;
    }
	z -> parent = father ;
	if ( father == nil ) root = z;
	else if (z -> key < father -> key ) father -> left = z;
    else father -> right = z ;
	z -> left = z -> right = nil ;
	z -> color = RED ;
	
	RBinsert_fixUp(z);
}


void RBTree :: RBinsert_fixUp(Node *z) {
    while (z -> parent -> color == RED ) {
	    if (z -> parent == z -> parent -> parent -> left ) {
 	 	    Node *uncle = z -> parent -> parent -> right ;
		    if ( uncle -> color == RED ) { 
 	 	  	    z -> parent -> color = BLACK ; 
		  	    uncle -> color = BLACK ; 
 	 	  	    z -> parent -> parent -> color = RED ; 
 	 	  	    z = z -> parent -> parent ; 
 	 	    } else {
 	 	 	     if (z == z -> parent -> right ) { 
 	 	  	  	      z = z -> parent ; 
 	 	  	  	      left_rotate (z) ; 
			    }
 	 	        z -> parent -> color = BLACK ; 
 	 	        z -> parent -> parent -> color = RED ; 
 	 	        right_rotate (z -> parent -> parent ); 
 	        }
        }
 	    else { 
		    Node *uncle = z -> parent -> parent -> left;
			if ( uncle -> color == RED ) { 
 	 	  	  z -> parent -> color = BLACK ; 
		  	  uncle -> color = BLACK ; 
 	 	  	  z -> parent -> parent -> color = RED ; 
 	 	  	  z = z -> parent -> parent ; 
 	 	    } else {
 	 	 	     if (z == z -> parent -> left ) { 
 	 	  	  	      z = z -> parent ; 
 	 	  	  	      right_rotate (z) ; 
			      }
 	 	         z -> parent -> color = BLACK ; 
 	 	         z -> parent -> parent -> color = RED ; 
 	 	         left_rotate (z -> parent -> parent ); 
            }	  

        }
    }
    root -> color = BLACK ; 
}

void RBTree :: RBpreorder(Node *node){
	if(node != nil) {
 		cout << "(" << node->key << ", " << node->value << ")" << endl;
 		RBpreorder(node->left);
 		RBpreorder(node->right);
	}
}

void RBTree :: RBpreorderA(){
	RBpreorderB();
}

void RBTree :: RBpreorderB(){
	Node *aux = root;
	RBpreorder(aux);
}

void RBTree :: remove ( const Tkey& key ) {
     Node *p = root ;
     while (p != nil && p -> key != key ) {
	    p = ( key < p -> key ) ? p -> left : p -> right ;
    }
	if(p != nil ) RBdelete (p);
}

void RBTree :: RBdelete(Node *z){
    Node *y;
    Node *x;
    if(z->left == nil || z->right == nil) y = z;
    else y = minimum(z->right);

    x->parent = y->parent;

    if(y->parent == nil) root = x;
    else{
        if(y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
    }
    if(y != z){
        z->key = y->key;
        z->value = y->value;
    }
    if(y->color == BLACK) RBdelete_fixUp(x);

    delete y;
}

void RBTree :: RBdelete_fixUp ( Node *x) {
	while (x != root && x -> color == BLACK ) {
		if (x == x -> parent -> left ) { 
			Node *w = x -> parent -> right ;
		    if (w -> color == RED ) { 
			    w -> color = BLACK ; 
			    x -> parent -> color = RED ; 
			    left_rotate (x -> parent ); 
			    w = x -> parent -> right ; 
            }

		    if (w -> left -> color == BLACK && w -> right -> color == BLACK ) { 
			    w -> color = RED ; 
			    x = x -> parent ; 
            } else {
		        if (w -> right -> color == BLACK ) { 
			        w -> left -> color = BLACK ; 
			        w -> color = RED ; 
			        right_rotate (w); 
			        w = x -> parent -> right ; 
                }

			    w -> color = x -> parent -> color ; 
			    x -> parent -> color = BLACK ;
			    w -> right -> color = BLACK ; 
			    left_rotate (x -> parent ); 
			    x = root ;
		    }
	    }
    }
		x -> color = BLACK ;
}

Node *RBTree :: minimum ( Node *node ) {
     while ( node -> left != nil ) {
	    node = node -> left ;
    }
	return node ;
}

int RBTree :: RBheight (Node *node){
		if(node == nil) return 0;
		if(node->left == nil && node->right == nil) return 1;
		int esq = RBheight(node->left);
		int dir = RBheight(node->right);
		if(esq>dir) return esq+1;
		return dir+1;
}
	
int RBTree :: Height1(){
	return Height2();
}

int RBTree :: Height2(){
	Node *aux = root;
	return RBheight(aux);
}

void RBTree :: delete_all(Node *node){
	if(node != nil){
		delete_all(node->left);
		delete_all(node->right);
		RBdelete(node);
	}
}

void RBTree :: delete_all2(){
	delete_all(root);
}

void RBTree :: delete_allPublic(){
	delete_all2();
}

bool RBTree :: search( const Tkey& key , const Tvalue& v){
	search2(key, v);
}

bool RBTree :: search2 (const Tkey& key , const Tvalue& v){
	Node *p = root;
	while(p!= nil && p -> key != key){
		p = ( key < p -> key ) ? p -> left : p -> right ; 
	}
	if(p != nil && p->value == v) return true;
	else false;
}

