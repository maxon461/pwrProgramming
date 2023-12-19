#ifndef CNUMBER_H
#define CNUMBER_H

#include <iostream>
#include <string>

class CNumber {
private:
    int *pi_table;
    int i_length;
    

public:
    CNumber();
    CNumber(const CNumber &other);
    CNumber& operator=(const int iValue);
    CNumber& operator=(const CNumber &other);


    friend CNumber &operator>=(int val , CNumber &other);
    friend int &operator>=( CNumber other , int &val  );
    CNumber &operator>=(CNumber &other);



    // friend bool operator>=( CNumber &obj , int &val);
    CNumber operator+(CNumber &other) ;
    CNumber operator-(const CNumber &other) ;
    CNumber operator*(const CNumber &other) const;
    CNumber operator/(CNumber &other) const;
    bool operator==(CNumber &other);
    bool operator>(CNumber &other) ;
    // CNumber checkSum(CNumber &obj ,CNumber &other) ;
    // void checkSub(CNumber &other) ;
    std::string sToStr() const;
    ~CNumber();
    int getLength() const;
    const int* getTable() const;
    const std::string subtractLargeNumbers(std::string num1, std::string num2);
    const bool checkVal() const;
};

#endif /* CNUMBER_H */
