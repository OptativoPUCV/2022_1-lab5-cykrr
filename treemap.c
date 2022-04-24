#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"


int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap *this = (TreeMap *)malloc(sizeof(TreeMap));
    this->root = NULL;
    

    this->lower_than = lower_than;
    return this;
}


void insertTreeMap(TreeMap * this, void* key, void * value) {
    TreeNode *new = createTreeNode(key, value);
    if(!this || !key) return;
    TreeNode *i = this->root;
    /*
    if(this == NULL ||
        this->root == NULL || 
        this->root->pair == NULL || 
        this->root->pair->key == NULL ||
        key == NULL) return NULL;
    */
    
    int j = 0;
    while(i) { 
        if(is_equal(this, key, i->pair->key)) {
            return;
        }        

        if(this->lower_than(key, i->pair->key))  {
            if(i->left) 
                i=i->left;
            else {
                i->left = new;
                new->parent = i;
                this->current = new;
            }

        } else {
            if(i->right) 
                i=i->right;
            else {
                i->right = new;
                new->parent = i;
                this->current = new;
            }
        }


        if(j >= 100) {
            printf("!!!! Tiempo de ejecucion excedido\n");
            exit(1);
        }
        j++;
    }

    this->current = new;
}

TreeNode * minimum(TreeNode * x){
    while(x->left) x = x->left;
    return x;
}

TreeNode * maximum(TreeNode *x) {
    if(x->right ){
        while(x->right) x = x->right;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    TreeNode *parent = node->parent;
    // si el nodo tiene hijos
    int count = (node->left != NULL) + (node->right != NULL);
    if (count == 0) { 
        // si estamos a la izquierda
        if(parent->left == node) {
            parent->left = NULL;
        } else if(parent->right == node){
            parent->right = NULL;
        }
        free(node);
    } else if(count == 1) {
        TreeNode * child;
        if(node->left) child = node->left;
        else child = node->right;
        if(parent->left == node) {
            parent->left = child;
        } else if(parent->right == node) {
            parent->right = child;
        }
        child->parent = parent;
        free(node);
    } else if(count == 2) {
        TreeNode *bigger = maximum(node->right->right);
        printf("bigger %d\n", *((int*)bigger->pair->key));
        node->pair = bigger->pair;
        removeNode(tree, bigger);
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * this, void* key) {
    if(!this || !key) return NULL;
    TreeNode *i = this->root;
    /*
    if(this == NULL ||
        this->root == NULL || 
        this->root->pair == NULL || 
        this->root->pair->key == NULL ||
        key == NULL) return NULL;
    */
    
    int j = 0;
    while(i) { 
        if(is_equal(this, i->pair->key, key)) break;
        if(this->lower_than(key, i->pair->key)) {
            i=i->left;
        } else {
           i = i->right;
        }


        if(j >= 100) {
            printf("!!!! Tiempo de ejecucion excedido\n");
            exit(1);
        }
        j++;
    }

    this->current = i;
    if(i != NULL)
        printf("!!Found key: %d\n", *(int*)(i->pair->key));
    else 
        printf("!! Found nothing.. \n");

    if(i == NULL) return NULL;
    else return i->pair;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
