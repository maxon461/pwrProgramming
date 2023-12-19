#include <iostream>
// #include <array>
#include "modific.h"

int **allocateIrregularArray2D(int arr[], int arrSize)
{
    std::cout << "The length of the array is: " << arrSize << "\n";
    if (arrSize < 1)
        return nullptr;
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] <= 0)
            return nullptr;
    }

    int **pi_table;
    pi_table = new int *[arrSize];

    for (int i = 0; i < arrSize; i++)
    {
        pi_table[i] = new int[arr[i]];
    }

    return pi_table;
}

void fillArray_(int **array, int rows, int arr[])
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < arr[i]; j++)
        {
            array[i][j] = rand() % 21 - 10;
            // std::cin >> array[i][j];
        }
    }
}

void printArray_(int **array, int rows, int arr[])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < arr[i]; j++)
        {
            std::cout << " " << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool b_dealloc_table_2_dim_(int **piTable, int iSizeX)
{ // dealloc
    for (int i = 0; i < iSizeX; i++)
        delete[] piTable[i];
    delete[] piTable;

    return true;
}

void modT()
{
    int lenArr[] = {3, 4, 5, 6};
    int al = sizeof(lenArr) / sizeof(lenArr[0]); // length calculation

    int **pi_table = allocateIrregularArray2D(lenArr, al);

    std::cout << pi_table << '\n';

    fillArray_(pi_table, al, lenArr);

    printArray_(pi_table, al, lenArr);

    b_dealloc_table_2_dim_(pi_table, al);

    // std::cout << pi_table << '\n';
}