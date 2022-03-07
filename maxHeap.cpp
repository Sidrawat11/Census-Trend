#include "maxHeap.h"
#include "utilities.h"
#include <math.h>
#include <cstring>

void buildMaxHeap(std::string fileName, std::string key, SOC occupations[])
{
    // Index of last non-leaf node
    int lnleaf = (NUM_OCC / 2) - 1;

    for (int i = lnleaf; i >= 0; i--)
    {
        maxHeapify(occupations, i, NUM_OCC, key);
    }

    // printArray(occupations);
}

void maxHeapify(SOC arr[], int i, int n, std::string key)
{

    if (key.compare("total") == 0)
    {
        int largest = i;   // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && arr[l].total > arr[largest].total)
        {
            largest = l;
        }
        else if (l < n && arr[l].total == arr[largest].total)
        {
            if (compareLexi(arr[l].occupation, arr[largest].occupation) == 1)
            {
                largest = l;
            }
        }

        // If right child is larger than largest so far
        if (r < n && arr[r].total > arr[largest].total)
        {
            largest = r;
        }
        else if (r < n && arr[r].total == arr[largest].total)
        {
            if (compareLexi(arr[r].occupation, arr[largest].occupation) == 1)
            {
                largest = r;
            }
        }

        // If largest is not root
        if (largest != i)
        {
            SOC temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            // Recursively heapify the affected sub-tree
            maxHeapify(arr, largest, n, key);
        }
    }
    else if (key.compare("male") == 0)
    {
        int largest = i;   // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && arr[l].male > arr[largest].male)
        {
            largest = l;
        }
        else if (l < n && arr[l].male == arr[largest].male)
        {
            if (compareLexi(arr[l].occupation, arr[largest].occupation) == 1)
            {
                largest = l;
            }
        }

        // If right child is larger than largest so far
        if (r < n && arr[r].male > arr[largest].male)
        {
            largest = r;
        }
        else if (r < n && arr[r].male == arr[largest].male)
        {
            if (compareLexi(arr[r].occupation, arr[largest].occupation) == 1)
            {
                largest = r;
            }
        }

        // If largest is not root
        if (largest != i)
        {
            SOC temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            // Recursively heapify the affected sub-tree
            maxHeapify(arr, largest, n, key);
        }
    }
    else if (key.compare("female") == 0)
    {
        int largest = i;   // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && arr[l].female > arr[largest].female)
        {
            largest = l;
        }
        else if (l < n && arr[l].female == arr[largest].female)
        {
            if (compareLexi(arr[l].occupation, arr[largest].occupation) == 1)
            {
                largest = l;
            }
        }

        // If right child is larger than largest so far
        if (r < n && arr[r].female > arr[largest].female)
        {
            largest = r;
        }
        else if (r < n && arr[r].female == arr[largest].female)
        {
            if (compareLexi(arr[r].occupation, arr[largest].occupation) == 1)
            {
                largest = r;
            }
        }

        // If largest is not root
        if (largest != i)
        {
            SOC temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            // Recursively heapify the affected sub-tree
            maxHeapify(arr, largest, n, key);
        }
        
    }
}

void deleteMax(SOC arr[], int n, int size, std::string key)
{
    // Printing Values on the console
    std::cout << "Top " << n << " occupations in 1999 for " << key << " workers:" << std::endl;
    while (n != 0)
    {
        // Get the last element
        SOC lastElement = arr[size - 1];

        if (key.compare("total") == 0)
        {
            std::cout << "\t" << convertToString(arr[0].occupation) << ": " << addCommas(arr[0].total) << std::endl;
        }
        else if (key.compare("male") == 0)
        {
            std::cout << "\t" << convertToString(arr[0].occupation) << ": " << addCommas(arr[0].male) << std::endl;
        }
        else if(key.compare("female") == 0)
        {
            std::cout << "\t" << convertToString(arr[0].occupation) << ": " << addCommas(arr[0].female) << std::endl;
        }

        // Replace root with last element
        arr[0] = lastElement;

        // Decrease size of heap by 1
        size--;
        n--;

        // heapify the root node
        maxHeapify(arr, 0, size, key);
    }

}