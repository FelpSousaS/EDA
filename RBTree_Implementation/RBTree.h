#ifndef RBTREE_H
#define RBTREE_H
#include "item.h"
#include "node.h"



class RBTree{
    private:
        Node *root;
        Node *nil;
    protected:
        void left_rotate(Node *node);
        void right_rotate(Node *node);
        void RBinsert(Node *node);
        void RBinsert_fixUp(Node *node);
        void RBdelete(Node *z);
        void RBdelete_fixUp(Node *z);
        Node *minimum(Node *node);
        void RBpreorder(Node *node);
        void RBpreorderB();
        int RBheight(Node *node);
        int Height2();
        void delete_all(Node *node);
        void delete_all2();
        bool search2(const Tkey& key, const Tvalue& v);
    public:
        RBTree();
        void insert(const Tkey& key, const Tvalue& value);
        void remove(const Tkey& key);
        bool search(const Tkey& key,const Tvalue& v);   
        void RBpreorderA();
        int Height1();
		bool empty()const;
        void delete_allPublic();
        
            
};

#endif