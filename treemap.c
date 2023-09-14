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
    
  if (tree == NULL) return;
    
  //TreeNode* current = NULL;
  Pair* existingPair = searchTreeMap(tree, key);
  
  if (existingPair != NULL) return;
    
  TreeNode* newNode = createTreeNode(key, value);

  if (newNode == NULL) return;
  if (tree -> root == NULL){
    tree -> root = newNode;
    tree -> current = newNode;
    return;
  }
  current = tree -> current;

  TreeNode* parent = NULL;
  TreeNode* currentChild = tree -> root;

   while (currentChild != NULL){
     parent = currentChild;
     if (tree -> lower_than(key, currentChild -> pair -> key)){
       currentChild = currentChild -> left;
        } 
     else currentChild = currentChild->right;
  }
  
  newNode -> parent = parent;

  if (tree -> lower_than(key, parent -> pair -> key)) parent -> left = newNode;
  else parent -> right = newNode;
  tree -> current = newNode;
  
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

Pair* searchTreeMapRecursive(TreeNode* node, void* key, int (*lower_than)(void* key1, void* key2), TreeNode** current){
  
  if (node == NULL){
    *current = NULL;
    return NULL;
  }

  int comparison = lower_than(key, node -> pair -> key);

  if(comparison == 0){
    *current = node;
    return node -> pair; 
  }  

  else if (comparison < 0) return searchTreeMapRecursive(node -> left, key, lower_than, current);

  else return searchTreeMapRecursive(node -> right, key, lower_than, current);

}

Pair * searchTreeMap(TreeMap * tree, void* key){
  
  if((tree == NULL) || (tree -> root == NULL)){
    tree -> current = NULL;
    return NULL;
  }

  TreeNode* current = NULL;
  Pair* result = searchTreeMapRecursive(tree->root, key, tree->lower_than, &current);
  tree -> current = current;

  return result;
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
