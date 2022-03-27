#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif
#include <iostream>
#include <string>

void buildMaxHeap(std::string fileName, std::string key, SOC occpations[]);
void maxHeapify(SOC arr[],int i, int n, std::string key);
void deleteMax(SOC arr[], int n, int size, std::string key);