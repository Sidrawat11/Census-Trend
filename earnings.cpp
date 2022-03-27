#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif
#include <iostream>
#include <string>
#include "utilities.h"
#include "maxHeap.h"
#include "BST.h"
#include "HashTable.h"
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
    // Create FileName to Read from
    string fileName = "Occupation-Dist-All-";
    fileName.append(argv[1]);
    fileName.append(".csv");
    bool earningsStructCreated = false;
    bool binaryHashCreated = false;

    earnings dataEarn[60];
    // This Array is common in the entire maxHeap file
    SOC occupations[NUM_OCC];

    // Root pointer for binary tree
    bst *root = new bst;
    root = NULL;

    bool isMaxHeap = false;
    int hashSize = 3 * NUM_OCC;

    while (!TestForPrime(hashSize))
    {
        hashSize++;
    }
    hash_table_entry **hashTable = new hash_table_entry *[hashSize];
    for (int i = 0; i < hashSize; i++)
        hashTable[i] = NULL;

    // Inputs the number of time query should run
    string query = "";
    string firstLine = ""; // FirstLine of queries.txt
    int QueryRuns;         // Number of queries to run

    // Takes in the firstline of the File
    getline(cin, firstLine);
    QueryRuns = stoi(firstLine);

    while (QueryRuns != 0)
    {
        // Take in the Query
        getline(cin, query);
        string keyWord = findTheNthWord(query, 0); // Find the first word and perform operation accordingly
        if (keyWord.compare("find") == 0)
        {
            keyWord = findTheNthWord(query, 1);

            if (keyWord.compare("max") == 0)
            {

                string key = findTheNthWord(query, 2);
                if (key.compare("total") == 0 || key.compare("male") == 0 || key.compare("female") == 0)
                {
                     cout << "Query: " << query << endl
                             << endl;
                    // Create The SOC array And populate it Using fileName
                    createSOCArray(fileName, occupations);
                    buildMaxHeap(fileName, key, occupations);
                    string times = findTheNthWord(query, 3);
                    deleteMax(occupations, stoi(times), NUM_OCC, key);
                    // if (!isMaxHeap)
                    // {
                    //     // Echo the Query On The Output File/Console
                       
                    //     cout << "Number of nodes: " << NUM_OCC << endl;
                    //     cout << "Height of tree: " << floor(log2(NUM_OCC)) << endl;
                    //     cout << "Height of left subtree: " << floor(log2(NUM_OCC)) << endl;
                    //     cout << "Height of right subtree: " << floor(log2(NUM_OCC)) - 1 << endl;
                    //     isMaxHeap = true;
                    // }
                }
                else
                {
                    cout << "Query Failed" << endl;
                }
            }
            if (keyWord.compare("ratio") == 0)
            {
                if (!earningsStructCreated)
                {
                    // Create The SOC array And populate it Using fileName
                    createEarningsArray("Earnings-1960-2019.csv", dataEarn);
                    earningsStructCreated = true;
                }
                // Echo the Query On The Output File/Console
                cout << "Query: " << query << endl
                     << endl;
                int beg = searchIndex(dataEarn, stoi(findTheNthWord(query, 2)));
                int end = searchIndex(dataEarn, stoi(findTheNthWord(query, 3)));
                if (end - beg > 60)
                {
                    cout << "Query Failed" << endl;
                }
                else
                {
                    findRatioInRange(dataEarn, beg, end);
                }
            }
            if (keyWord.compare("occupation") == 0)
            {
                 string toFind = findTheNthWord(query, 3);
                    cout << "Query: " << query << endl
                         << endl;
                if (!binaryHashCreated)
                {
                   
                    // Create The SOC array And populate it Using fileName
                    root = buildBinaryTree(fileName, root, hashTable, hashSize);
                    binaryHashCreated = true;
                    // cout << "Total Height of BST: " << countHeight(root) << endl;
                    // cout << "Height of left subtree: " << countHeight(root->left) << endl;
                    // cout << "Height of right subtree: " << countHeight(root->right) << endl;
                    // cout << "Total Number of Nodes: " << numberOfNodes(root) << endl;

                    // int entry = printHash(hashTable, hashSize);

                    // float loadFactor = (float)entry/hashSize;

                    // printf("Load Factor: %.2f\n\n", loadFactor);
                }

                findHashEntry(toFind, hashSize, hashTable);
            }
        }
        else
        {
            if (!binaryHashCreated)
            {
                // Create The SOC array And populate it Using fileName
                root = buildBinaryTree(fileName, root, hashTable, hashSize);
                binaryHashCreated = true;
            }
            cout << "Query: " << query << endl
                 << endl;
            cout << "The occupations in the range " << findTheNthWord(query, 2) << " to " << findTheNthWord(query, 3) << ":" << endl;
            if (countNode(root, findTheNthWord(query, 2), findTheNthWord(query, 3)) > 0)
            {
                inOrderPrint(root, findTheNthWord(query, 2), findTheNthWord(query, 3));
            }
            else
            {
                cout << "\tNo occupations found in the given range" << endl;
            }
        }
        // Decrease QueryRuns
        --QueryRuns;
    }

    return 0;
}