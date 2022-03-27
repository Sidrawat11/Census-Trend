#include "utilities.h"
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <locale>
#include <sstream>

// Returns the word at nth position in the string; Enter n-1 to get word at nth position
std::string findTheNthWord(std::string line, int wordPos)
{
    std::string returnVal = "";
    int n = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line.at(i) == ' ')
        {
            if (n == wordPos)
                break;
            else
            {
                returnVal = "";
                n++;
            }
        }
        else
        {
            returnVal += line.at(i);
        }
    }
    return returnVal;
}

void printNode(SOC *src)
{
    std::cout << "Occupation: " << src->occupation << "  SOC-CODE: " << src->SOC_code << std::endl;
    std::cout << "Total: " << src->total << std::endl;
    std::cout << "Female: " << src->female << std::endl;
    std::cout << "Male: " << src->male << std::endl;
}

void printArray(SOC printArr[])
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "\t\t#######################  " << i + 1 << "  #######################" << std::endl;
        std::cout << "Occupation: " << printArr[i].occupation << "  SOC-CODE: " << printArr[i].SOC_code << std::endl;
        std::cout << "Total: " << printArr[i].total << std::endl;
        std::cout << "Female: " << printArr[i].female << std::endl;
        std::cout << "Male: " << printArr[i].male << std::endl
                  << std::endl
                  << std::endl;
    }
}

std::string convertToString(char arr[])
{
    std::string returnVal;
    int i = 0;
    while (arr[i] != '\0')
    {
        returnVal += arr[i];
        i++;
    }
    return returnVal;
}

int compareLexi(char str[], char str2[])
{
    std::string s1 = convertToString(str);
    std::string s2 = convertToString(str2);
    if (s1.compare(s2) > 0)
    {
        return 1;
    }
    else if (s1.compare(s2) < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

std::string convertString(std::string str)
{
    std::string returnVal;
    for (int i = 0; i < str.length(); i++)
    {
        if (str.at(i) >= 48 && str.at(i) <= 57)
        {
            returnVal += str.at(i);
        }
    }
    return returnVal;
}

void createSOCArray(std::string fileName, SOC arr[])
{
    std::ifstream newFile;
    newFile.open(fileName);
    std ::string current = "";
    int row = 0, columns = 0, lineNum = 0;
    std::string columns_value = "";
    while (!newFile.eof())
    {

        if (lineNum < 1)
        {
            getline(newFile, current);
            lineNum++;
        }
        else
        {
            columns = 0;
            bool inQuotes = false;
            int val = 0;
            getline(newFile, current);
            int cursor = 0;
            while (cursor < current.length())
            {
                // This will check if current cursor is in Quotes
                if (current.at(cursor) == '\"')
                {
                    inQuotes = true;
                    cursor++;
                    while (inQuotes)
                    {
                        columns_value += current.at(cursor);
                        cursor++;
                        if (current.at(cursor) == '\"')
                        {
                            inQuotes = false;
                            cursor++;
                            if (cursor == current.length() && row == 504)
                            {
                                val = std::stoi(convertString(columns_value.substr(0, columns_value.length())));
                                arr[row].male = val;
                                columns_value = "";
                                cursor++;
                            }
                        }
                    }
                }
                else
                {
                    // When encountered a comma fill column value
                    if (current.at(cursor) == ',' || current.at(cursor) == '\r')
                    {
                        switch (columns)
                        {
                        case 0:
                            columns_value.copy(arr[row].occupation, columns_value.length());
                            // TO end every CHAR [] with null
                            arr[row].occupation[columns_value.length()] = '\0';
                            columns++;
                            cursor++;
                            columns_value = "";
                            break;
                        case 1:
                            columns_value.copy(arr[row].SOC_code, columns_value.length());
                            // TO end every CHAR[] with null
                            arr[row].SOC_code[columns_value.length()] = '\0';
                            columns++;
                            cursor++;
                            columns_value = "";
                            break;
                        case 2:
                            val = std::stoi(convertString(columns_value));
                            arr[row].total = val;
                            columns_value = "";
                            cursor++;
                            columns++;
                            break;
                        case 3:
                            val = std::stoi(convertString(columns_value));
                            arr[row].female = val;
                            columns_value = "";
                            cursor++;
                            columns++;
                            break;
                        case 4:
                            val = std::stoi(convertString(columns_value.substr(0, columns_value.length())));
                            arr[row].male = val;
                            columns_value = "";
                            cursor++;
                            columns++;
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        columns_value += current.at(cursor);
                        cursor++;
                    }
                }
            }

            row++;
        }
    }
}

void createEarningsArray(std::string fileName, earnings earningsAray[])
{
    std::ifstream newFile;
    newFile.open(fileName);
    bool inQuotes = false;
    std::string currentLine = "";
    int rows = 0;
    int lineNum = 0;
    int columns;

    while (!newFile.eof())
    {
        if (lineNum < 1)
        {
            getline(newFile, currentLine);
            lineNum++;
        }
        else
        {
            getline(newFile, currentLine);
            int i = 0;
            columns = 0;
            std::string columnVal = "";
            while (i < currentLine.length())
            {
                if (currentLine.at(i) == '\"')
                {
                    inQuotes = true;
                    i++;
                    while (inQuotes)
                    {
                        columnVal += currentLine.at(i);
                        i++;
                        if (currentLine.at(i) == '\"')
                        {
                            inQuotes = false;
                            i++;
                        }
                    }
                }
                else if (currentLine.at(i) == ',')
                {
                    if (columnVal.compare("N") == 0)
                    {
                        columnVal = "0";
                    }
                    switch (columns)
                    {
                    case 0:
                        earningsAray[rows].year = std::stoi(columnVal);
                        columnVal = "";
                        columns++;
                        i++;
                        break;
                    case 1:
                        earningsAray[rows].male_total = std::stoi(convertString(columnVal));
                        columnVal = "";
                        columns++;
                        i++;
                        break;

                    case 2:
                        earningsAray[rows].male_with_earnings = std::stoi(convertString(columnVal));
                        columnVal = "";
                        columns++;
                        i++;
                        break;

                    case 3:
                        earningsAray[rows].male_earnings = std::stoi(convertString(columnVal));
                        columnVal = "";
                        columns++;
                        i++;
                        break;

                    case 4:
                        earningsAray[rows].male_earnings_moe = std::stoi(convertString(columnVal));
                        columnVal = "";
                        columns++;
                        i++;
                        break;

                    case 5:
                        earningsAray[rows].female_total = std::stoi(convertString(columnVal));
                        columnVal = "";
                        columns++;
                        i++;
                        break;

                    case 6:
                        earningsAray[rows].female_with_earnings = std::stoi(convertString(columnVal));
                        columnVal = "";
                        columns++;
                        i++;
                        break;

                    case 7:
                        earningsAray[rows].female_earnings = std::stoi(convertString(columnVal));
                        columnVal = "";
                        columns++;
                        i++;
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    if (currentLine.at(i) == '\r')
                    {
                        if (columnVal.compare("N") == 0)
                        {
                            columnVal = "0";
                        }
                        earningsAray[rows].female_earnings_moe = std::stoi(convertString(columnVal));
                        columnVal = "";
                        i++;
                    }
                    else
                    {
                        columnVal += currentLine.at(i);
                        i++;
                    }
                }
            }
            rows++;
        }
    }
}

int searchIndex(earnings arr[], int num)
{
    int returnVal;
    for (int i = 0; i < 60; i++)
    {
        if (arr[i].year == num)
        {
            returnVal = i;
            break;
        }
    }
    return returnVal;
}

std::string decimalTillFirst(std::string num)
{
    std::string vals;
    for (int i = 0; i < num.length(); i++)
    {
        if (num.at(i) == '.')
        {
            int j = i + 1;
            vals += num.at(i);
            vals += num.at(j);
            break;
        }
        else
        {
            vals += num.at(i);
        }
    }
    return vals;
}

void findRatioInRange(earnings arr[], int beg, int end)
{
    double ratio;
    double female;
    double male;
    std::cout << "The female-to-male earnings ratio for " << arr[beg].year << "-" << arr[end].year << ":" << std::endl;
    for (int i = beg; i >= end; i--)
    {
        female = (double)arr[i].female_earnings;
        male = (double)arr[i].male_earnings;
        ratio = (female / male) * 100;
        std::string finalAnswer = std::to_string(ratio);
        std::cout << "\t" << arr[i].year << ": " << decimalTillFirst(finalAnswer) << "%" << std::endl;
    }
}

std::string addCommas(int num)
{
    std::string returnVal = std::to_string(num);
    std::string rev = "";
    if (returnVal.length() > 3)
    {
        int thousands = 0;
        for (int i = returnVal.length() - 1; i >= 0; i--)
        {
            rev.push_back(returnVal.at(i));
            thousands++;
            if (thousands == 3 && i != 0)
            {
                thousands = 0;
                rev.push_back(',');
            }
        }
        returnVal = "";
        for (int i = rev.length() - 1; i >= 0; i--)
        {
            returnVal.push_back(rev.at(i));
        }
        return returnVal;
    }
    else
    {
        return returnVal;
    }
}

bool TestForPrime(int val)
{
    int limit, factor = 2;
    limit = (long)(sqrtf((float)val) + 0.5f);
    while ((factor <= limit) && (val % factor))
        factor++;
    return (factor > limit);
}