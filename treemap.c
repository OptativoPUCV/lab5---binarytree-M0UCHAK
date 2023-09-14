#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

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

int lower_than(void* key1, void* key2){
  
    int* int_key1 = (int*)key1;
    int* int_key2 = (int*)key2;
    return (*int_key1 < *int_key2);
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)){

  TreeMap* map = (TreeMap*)malloc(sizeof(TreeMap));
  if (map == NULL) return NULL;
    
  map -> root = NULL;
  map -> current = 0;

  if (lower_than != NULL) map -> lower_than = lower_than;
  else map -> lower_than = lower_than;

  return map;
}

void insertTreeMap(TreeMap * tree, void* key, void * value){
  if((tree == NULL) || (tree -> root == NULL)){
    tree -> current = NULL;
    return NULL;
  }
  
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
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