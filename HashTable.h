#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif
#include <iostream>
#include <string>

void intialiseHashMap(hash_table_entry* map[]);
void put(hash_table_entry* table[],int key, bst *node);

int hash(int value, int size);

void findHashEntry(std::string soc,int size, hash_table_entry** table);

// int printHash(hash_table_entry **table, int hashsize);