#include "utilities.h"
#include <cstring>

void put(hash_table_entry **table, int key, bst *value)
{
    hash_table_entry *tempNode = NULL;
    hash_table_entry *newNode = table[key];
    while (newNode != NULL)
    {
        tempNode = newNode;
        newNode = newNode->next;
    }
    if (newNode == NULL)
    {
        newNode = new hash_table_entry;
        newNode->node = value;
        newNode->next = NULL;
        strcpy(newNode->SOC_code, value->soc.SOC_code);
        if (tempNode == NULL)
        {
            table[key] = newNode;
        }
        else
        {
            tempNode->next = newNode;
        }
    }
    else
    {
        newNode->node = value;
    }
}

int hash(int val, int size)
{
    return (val % size);
}

void printHashEntry(hash_table_entry *val)
{
    std::cout << "\t" << val->node->soc.occupation << ": ";
    std::cout << "YRFT: " << addCommas(val->node->soc.total) << ", ";
    std::cout << "Female: " << addCommas(val->node->soc.female) << ", ";
    std::cout << "Male: " << addCommas(val->node->soc.male) << std::endl;
}

void findHashEntry(std::string soc, int size, hash_table_entry **table)
{
    int index = hash(std::stoi(convertString(soc)), size);
    bool found = false;
    std::string check = convertString(soc);
    hash_table_entry *tempNode = table[index];
    std::string code = convertToString(table[index]->SOC_code);
    std::string keyString = "";
    if (tempNode != NULL)
    {
        while (tempNode != NULL)
        {
            for (int i = 0; i < code.length(); i++)
            {
                if (code.at(i) == ',' || code.at(i) == '&' || i == code.length() - 1)
                {
                    if (i == code.length() - 1)
                        keyString += code.at(i);
                    if (keyString == "")
                        continue;
                    if (keyString == check)
                    {
                        std::cout << "The occupation with SOC code " << soc << ":" << std::endl;
                        printHashEntry(table[index]);
                        found = true;
                    }
                    keyString = "";
                }
                if (code.at(i) >= 48 && code.at(i) <= 57)
                {
                    keyString += code.at(i);
                }
            }

            tempNode = tempNode->next;
        }
    }
    if (!found)
    {
        std::cout << "The occupation with SOC code " << soc << " not found" << std::endl;
    }
}


/*For Experminetation

int maxLength(hash_table_entry **table, int size)
{
    int max = -1;
    int localMax = 0;
    for (int i = 0; i < size; i++)
    {
        localMax = 0;
        if (table[i] != NULL)
        {
            hash_table_entry *newNode = table[i];
            while (newNode != NULL)
            {
                newNode = newNode->next;
                localMax++;
            }
        }
        if (localMax > max)
        {
            max = localMax;
        }
    }
    return max;
}
int numberOflength(int target, hash_table_entry **table, int size)
{
    int localMax = 0;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        localMax = 0;
        if (table[i] != NULL)
        {
            hash_table_entry *newNode = table[i];
            while (newNode != NULL)
            {
                newNode = newNode->next;
                localMax++;
            }
            if (localMax == target)
            {
                count++;
            }
        }
    }
    return count;
}

int printHash(hash_table_entry **table, int size)
{
    int rows = maxLength(table, size);
    int entries = 0;
    std::cout << std::endl
              << "Length\t|\tNumber" << std::endl;
    for (int i = 0; i <= rows; i++)
    {
        std::cout << i << "\t|\t" << numberOflength(i, table, size) << std::endl;
        entries = entries + i*numberOflength(i, table, size);
    }

    return entries;
}

*/