#include <iostream>
#include "CTable.h"

class CTable
{
private:
    int *pi_table;
    int iTableLen;
    static const int default_length = 10;
    std::string s_name;

public:
    CTable()
    {
        s_name = "None";
        std::cout << "bezp " << s_name << '\n';
        iTableLen = default_length;
        pi_table = new int[iTableLen];
    };
    CTable(std::string sName, int iTableLen)
    {
        s_name = sName;
        std::cout << "parametr: '" << s_name << "'" << std::endl;
        pi_table = new int[iTableLen];
        iTableLen = iTableLen;
    }

    CTable(CTable &pcOther)
    {
        s_name = pcOther.s_name + "_copy";
        std::cout << "kopiuj: '" << s_name << "'" << std::endl;
        pi_table = new int[pcOther.iTableLen];
        iTableLen = pcOther.iTableLen;
    }

    ~CTable()
    {
        std::cout << "Usuwam " << s_name << '\n';
        delete[] pi_table;
    };

    void vSetName(std::string sName)
    {
        this->s_name = sName;
    }
    bool bSetNewSize(int iTableLen)
    {
        if (iTableLen <= 0)
        {
            std::cout << "Nieprawidłowa długość tablicy." << std::endl;
            return false;
        }

        int *newTable = new int[iTableLen];
        for (int i = 0; i < std::min(this->iTableLen, iTableLen); i++)
        {
            newTable[i] = pi_table[i];
        }

        delete[] pi_table;
        pi_table = newTable;
        this->iTableLen = iTableLen;

        return true;
    }

    CTable *pcClone()
    {
        return new CTable(*this);
    }

    int getTableLen()
    {
        return this->iTableLen;
    }
    void setTableLen(int iSize)
    {
        this->iTableLen = iSize;
    }
    int *getTab()
    {
        return pi_table;
    }
    void clearTab()
    {
        delete[] pi_table;
    }
    void setNewTab(int *newTab)
    {
        pi_table = newTab;
    }
};

void v_mod_tab(CTable *pcTab, int iNewSize)
{
    if (iNewSize <= 0)
    {
        std::cout << "Nieprawidłowa długość tablicy." << std::endl;
        return;
    }

    int *newTable = new int[iNewSize];
    int minSize = std::min(pcTab->getTableLen(), iNewSize);

    for (int i = 0; i < minSize; i++)
    {
        newTable[i] = pcTab->getTab()[i];
    }

    delete[] pcTab->getTab();
    pcTab->setNewTab(newTable);
    pcTab->setTableLen(iNewSize);
}

void v_mod_tab(CTable cTab, int iNewSize)
{
    if (iNewSize <= 0)
    {
        std::cout << "Nieprawidłowa długość tablicy." << std::endl;
    }

    int *newTable = new int[iNewSize];

    for (int i = 0; i < std::min(cTab.getTableLen(), iNewSize); i++)
    {
        newTable[i] = cTab.getTab()[i];
    }

    cTab.clearTab(); // delete[] pi_table;
    cTab.setNewTab(newTable);
    cTab.setTableLen(iNewSize);
}

void CTable_test(){
    CTable obj1 ;
    obj1.vSetName("Table1");
    obj1.bSetNewSize(15);

    CTable obj2("Table2", 5);
    obj2.vSetName("Table2");
    obj2.bSetNewSize(8);

    CTable obj3(obj2);
    obj3.vSetName("Table3");

    CTable c_tab;
    CTable *pc_new_tab;
    pc_new_tab = c_tab.pcClone();

    v_mod_tab(obj2, 2);
    std::cout << obj2.getTableLen() << std::endl;
    v_mod_tab(&obj2, 2);
    std::cout << obj2.getTableLen() << std::endl;
}

