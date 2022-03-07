#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif
#include <iostream>
#include <string>
#include "utilities.h"
#include "maxHeap.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Create FileName to Read from
    string fileName = "Occupation-Dist-All-";
    fileName.append(argv[1]);
    fileName.append(".csv");
    bool earningsStructCreated = false;

    earnings dataEarn[60];
    // This Array is common in the entire maxHeap file
    SOC occupations[NUM_OCC];

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
                // Echo the Query On The Output File/Console
                cout << "Query: " << query << endl << endl;
                string key = findTheNthWord(query, 2);
                // Create The SOC array And populate it Using fileName
                createSOCArray(fileName, occupations, key);
                buildMaxHeap(fileName, key, occupations);
                string times =findTheNthWord(query,3);
                deleteMax(occupations, stoi(times), NUM_OCC, key); 
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
                findRatioInRange(dataEarn, beg, end);
            }
        }

        // Decrease QueryRuns
        --QueryRuns;
    }

    return 0;
}