#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif
#include <iostream>
#include <string>

std::string findTheNthWord(std::string line, int wordPos);

void printArray(SOC printArr[]);

std::string convertString(std::string str);

std::string returnQuoted(std::string str);

void createSOCArray(std::string fileName, SOC arr[]);

std::string convertToString(char arr[]);

void printNode(SOC* src);

void createEarningsArray(std::string fileName, earnings earningsAray[]);

void findRatioInRange(earnings arr[], int beg, int end);

int searchIndex(earnings arr[], int num);

std::string decimalTillFirst(std::string);

int compareLexi(char str[], char str2[]);

std::string addCommas(int num);

bool TestForPrime(int val);


