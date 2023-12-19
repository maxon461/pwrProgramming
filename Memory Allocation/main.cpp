#include <iostream>
#include <array>
#include "CTable.cpp"
#include "modific.cpp"

void display(int arr[], int iSize)
{
    for (int i = 0; i < iSize; i++)
        std::cout << arr[i] << " ";
}

void v_alloc_table_fill_34(int iSize)
{
    int *res = new int[iSize];

    for (int i = 0; i < iSize; i++)
    {
        res[i] = 34;
    }

    display(res, iSize);
    delete[] res;
}
void fillArray(int **array, int rows, int columns)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            array[i][j] = rand() % 21 - 10;
            // std::cin >> array[i][j];
        }
    }
}

void printArray(int **array, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << " " << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool b_dealloc_table_2_dim(int **piTable, int iSizeX)
{ // dealloc
    for (int i = 0; i < iSizeX; i++)
        delete[] piTable[i];
    delete[] piTable;

    return true;
}

void b_alloc_table_2dim(int ***piTable, int iSizeX, int iSizeY)
{
    if (iSizeX <= 0 || iSizeY <= 0)
    {
        std::cout << "Invalid size values" << std::endl;
        return;
    }

    *piTable = new int *[iSizeX];
    for (int i = 0; i < iSizeX; i++)
    {
        (*piTable)[i] = new int[iSizeY]; // deref
    }
}

int main()
{
    int n = 3;
    // std::cout << "Type your's size ->  ";
    // std::cin >> n;

    if (n >= 0)
        v_alloc_table_fill_34(n);
    else
        std::cout << "Invalid Size value , try again ;(" << std::endl;

    // ***array
    int **pi_table;
    b_alloc_table_2dim(&pi_table, 5, 5);

    std::cout << pi_table << '\n';

    fillArray(pi_table, 5, 5);

    printArray(pi_table, 5, 5);

    b_dealloc_table_2_dim(pi_table, 5);

    // CTable

    CTable_test();

    int lenArr[] = {3, 4, 5, 6};
    int al = sizeof(lenArr) / sizeof(lenArr[0]); // length calculation

    int **Ipi_table = allocateIrregularArray2D(lenArr, al);

    std::cout << Ipi_table << '\n';

    fillArray_(Ipi_table, al, lenArr);

    printArray_(Ipi_table, al, lenArr);

    b_dealloc_table_2_dim_(Ipi_table, al);
    return 0;
}

// last question (ASCII and arr of String)