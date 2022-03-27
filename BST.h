#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif
#include <iostream>
#include <string>

bst *buildBinaryTree(std::string fileName, bst *root, hash_table_entry* table[], int size);

bst *createLeaf(SOC key);

bst *addLeaf(SOC key, bst *node, hash_table_entry* table[], int size);

void inOrderPrint(bst* root, std::string low, std::string high);

int countNode(bst* root, std::string low, std::string high);

// int countHeight(bst* node);

// int numberOfNodes(bst* node);
