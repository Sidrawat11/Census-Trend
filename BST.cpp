#include "utilities.h"
#include "BST.h"
#include "HashTable.h"
#include <iostream>
#include <string>
#include <cstring>

std::string removeQuotes(std::string val)
{
    std::string returnVal = "";
    for (int i = 0; i < val.length(); i++)
    {
        if (val.at(i) != '\"')
            returnVal += val.at(i);
    }
    return returnVal;
}

bst *createLeaf(SOC key)
{
    bst *leaf = new bst;
    leaf->soc = key;
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
}

bst *addLeafNode(SOC key, bst *current, hash_table_entry *table[], int size)
{
    if (current == NULL)
    {
        current = createLeaf(key);
        // Adding into hashTable
        std::string code = convertToString(current->soc.SOC_code);
        std::string keyString = "";
        for (int i = 0; i < code.length(); i++)
        {
            // If encounter a comma || & || code.length - 1 hash it to a value
            if (code.at(i) == ',' || code.at(i) == '&' || i == code.length() - 1)
            {
                if (i == code.length() - 1)
                    keyString += code.at(i);
                if (keyString == "")
                    continue;
                int key = hash(std::stoi(keyString), size);
                put(table, key, current);
                keyString = "";
            }
            // Add numbers into string
            if (code.at(i) >= 48 && code.at(i) <= 57)
            {
                keyString += code.at(i);
            }
        }
    }
    else if (strcmp(key.occupation, current->soc.occupation) < 0)
    {
        current->left = addLeafNode(key, current->left, table, size);
    }
    else
    {
        current->right = addLeafNode(key, current->right, table, size);
    }

    return current;
}

bst *buildBinaryTree(std::string fileName, bst *root, hash_table_entry *table[], int size)
{
    SOC arr[NUM_OCC];
    createSOCArray(fileName, arr);
    for (int i = 0; i < NUM_OCC; i++)
    {
        root = addLeafNode(arr[i], root, table, size);
    }

    return root;
}

void printNode(bst *val)
{
    std::cout << "\t" << val->soc.occupation << ": ";
    std::cout << "YRFT: " << addCommas(val->soc.total) << ", ";
    std::cout << "Female: " << addCommas(val->soc.female) << ", ";
    std::cout << "Male: " << addCommas(val->soc.male) << std::endl;
}

void inOrderPrint(bst *node, std::string low, std::string high)
{
    if (node == NULL)
    {
        return;
    }
    inOrderPrint(node->left, removeQuotes(low), removeQuotes(high));
    // Removing Double Quotes and converting high and low to char[]
    char l[removeQuotes(low).length() + 1];
    strcpy(l, removeQuotes(low).c_str());
    char h[removeQuotes(high).length() + 1];
    strcpy(h, removeQuotes(high).c_str());
    // If in range then print
    if (strcmp(l, node->soc.occupation) <= 0 && strcmp(h, node->soc.occupation) >= 0)
    {
        printNode(node);
    }
    inOrderPrint(node->right, removeQuotes(low), removeQuotes(high));
}

int countNode(bst *node, std::string low, std::string high)
{
    if (node == NULL)
        return 0;
    // Removing Double Quotes and converting high and low to char[]
    char l[removeQuotes(low).length() + 1];
    strcpy(l, removeQuotes(low).c_str());
    char h[removeQuotes(high).length() + 1];
    strcpy(h, removeQuotes(high).c_str());
    // If Node value is in range recursively call right&left subtrees
    if (strcmp(l, node->soc.occupation) <= 0 && strcmp(h, node->soc.occupation) >= 0)
    {
        return 1 + countNode(node->left, removeQuotes(low), removeQuotes(high)) + countNode(node->right, removeQuotes(low), removeQuotes(high));
    }
    else if (strcmp(l, node->soc.occupation) >= 0) // If current in less than low then check right subtree
    {
        return countNode(node->right, removeQuotes(low), removeQuotes(high));
    }
    else
    {
        return countNode(node->left, removeQuotes(low), removeQuotes(high));
    }
}

