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
/////////////////////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////////////////////////////

void insertTreeMap(TreeMap * tree, void* key, void * value){
    
  if (tree == NULL) return;
    
  TreeNode* current = NULL;
  if(current != NULL) return;
  
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
/////////////////////////////////////////////////////////////////////////////////////////

TreeNode * minimum(TreeNode * x){
  if (x == NULL) return NULL;
    
  while (x -> left != NULL) {
    x = x -> left;
  }
  return x;
}

/////////////////////////////////////////////////////////////////////////////////////////

void removeNode(TreeMap * tree, TreeNode* node){

  if (tree == NULL || node == NULL) return; 
    
  TreeNode* parent = node->parent;

  if ((node -> left == NULL) && (node -> right == NULL)){
    if (parent != NULL){
      if (parent -> left == node) parent -> left = NULL;
      else parent -> right = NULL;
    } 
    else tree -> root = NULL;
        
    free(node);
  }
  else if ((node -> left == NULL) || (node -> right == NULL)){
    TreeNode* child = (node -> left != NULL) ? node -> left : node -> right;
    if (parent != NULL){
      if (parent -> left == node) parent -> left = child;
      else parent -> right = child;
            
      child -> parent = parent;
    } 
    else{
      tree -> root = child;
      child -> parent = NULL;
    }
    free(node);
  }
  else{
    TreeNode* minRightSubtree = minimum(node->right); 
    Pair* tempPair = node -> pair;
    node -> pair = minRightSubtree -> pair; 
    minRightSubtree -> pair = tempPair;
    removeNode(tree, minRightSubtree);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}
/////////////////////////////////////////////////////////////////////////////////////////
Pair* searchTreeMap(TreeMap* tree, void* key){
  
  if ((tree == NULL) || (tree -> root == NULL)){
    return NULL;
  }

  TreeNode* aux = tree -> root;
  while(aux != NULL){
    if(is_equal(tree,key,aux -> pair -> key)){
      tree -> current = aux;
      return aux -> pair;
    }
    else if(tree -> lower_than(key, aux -> pair -> key)) aux = aux -> left;
    else aux = aux -> right;
  }
  return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////

Pair* upperBound(TreeMap* tree, void* key){
  
  if ((tree == NULL) || (tree -> root == NULL)) return NULL;

  TreeNode* aux = tree -> root;
  Pair* upper = NULL;

  while (aux != NULL){
    if (tree -> lower_than(aux -> pair -> key,key)) aux = aux -> right;   
    else{
      upper = aux -> pair;
      aux = aux -> left;
    }  
  }

  if (upper != NULL){
    tree -> current = aux;
    return upper;
  } 
  else return NULL;
    
}


/////////////////////////////////////////////////////////////////////////////////////////

Pair* firstTreeMap(TreeMap* tree){
    
  if ((tree == NULL) || (tree -> root == NULL)) return NULL;
    
  TreeNode* current = tree -> root;

  while (current -> left != NULL) {
    current = current -> left;
  }

  tree -> current = current;
  return current -> pair;
}
/////////////////////////////////////////////////////////////////////////////////////////

Pair* nextTreeMap(TreeMap* tree){
  if ((tree == NULL) || (tree -> current == NULL)) return NULL; 
    
  TreeNode* current = tree -> current;

  if (current -> right != NULL){
    current = current -> right;

    while (current -> left != NULL){
      current = current -> left;
    }

    tree -> current = current;
    return current -> pair;
  }

    TreeNode* parent = current -> parent;
    while ((parent != NULL) && (current == parent -> right)){
        current = parent;
        parent = parent -> parent;
    }

    tree -> current = parent;
    return (parent != NULL) ? parent -> pair : NULL;
}