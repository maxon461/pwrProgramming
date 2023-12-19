#include "CNumber.h"
#include <iostream>
#include <sstream>
#include <string>

CNumber::CNumber() : pi_table(nullptr), i_length(0) {}

CNumber::CNumber(const CNumber &other) : i_length(other.i_length)
{
    if (i_length > 0)
    {
        pi_table = new int[i_length];
        for (int i = 0; i < i_length; i++)
        {
            pi_table[i] = other.pi_table[i];
        }
    }
}

CNumber &CNumber::operator=(const int iValue)
{
    if (pi_table)
    {
        delete[] pi_table;
    }

    i_length = 1;
    pi_table = new int[i_length];
    pi_table[0] = iValue;

    return (*this);
}

CNumber &CNumber::operator=(const CNumber &other)
{
    if (this == &other)
    {
        return *this;
    }

    if (this->pi_table)
    {
        delete[] pi_table;
    }

    this->i_length = other.i_length;

    if (this->i_length > 0)
    {
        this->pi_table = new int[i_length];
        for (int i = 0; i < i_length; i++)
        {
            this->pi_table[i] = other.pi_table[i];
        }
    }

    return (*this);
}

CNumber::~CNumber()
{
    if (pi_table)
    {
        delete[] pi_table;
    }
}

CNumber CNumber::operator+(CNumber &other)
{

    CNumber res;
    res = 0;
    // res = checkSum((*this), other);
    if (!(res.pi_table[0] == 0))
        return res;
    std::string result;
    int carry = 0;
    std::string num1 = this->sToStr();
    std::string num2 = other.sToStr();

    int i = num1.size() - 1;
    int j = num2.size() - 1;

    int temp = res.i_length - 1;

    while (i >= 0 || j >= 0 || carry)
    {
        int x = (i >= 0) ? num1[i] - '0' : 0; // ASCII
        int y = (j >= 0) ? num2[j] - '0' : 0; // ASCII

        int sum = x + y + carry;
        carry = sum / 10;

        result = std::to_string(sum % 10) + result;

        i--;
        j--;
    }
    result.erase(0, result.find_first_not_of('0'));
    res.i_length = result.size();
    res.pi_table = new int[res.i_length];
    for (int k = 0; k < res.i_length; k++)
    {
        res.pi_table[k] = result[k] - '0';
    }

    return CNumber(res);
}

CNumber CNumber::operator-(const CNumber &other)
{
    CNumber res;
    res = 0;
    std::string result;
    int borrow = 0;

    std::string num1 = this->sToStr();
    std::string num2 = other.sToStr();

    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0)
    {
        int x = (i >= 0) ? num1[i] - '0' : 0;
        int y = (j >= 0) ? num2[j] - '0' : 0;

        int diff = x - y - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result = std::to_string(diff) + result;

        i--;
        j--;
    }

    // Usuń wiodące zera z wyniku, jeśli istnieją
    // result.erase(0, result.find_first_not_of('0'));
    result.erase(0, result.find_first_not_of('0'));
    if (result.empty())
    {

        return res;
    }
    int flag = 1;
    // Jeśli wynik jest ujemny, dodaj znak minus
    if (borrow == 1)
    {
        flag = -1;
        result = (subtractLargeNumbers(num2, num1)); // zabralem const na koncu
    }
    res.i_length = result.size();
    res.pi_table = new int[res.i_length];
    res.pi_table[0] = flag * (result[0] - '0');
    for (int k = 1; k < res.i_length; k++)
    {
        res.pi_table[k] = result[k] - '0';
    }
    return CNumber(res);
}

CNumber CNumber::operator*(const CNumber &other) const
{
    CNumber res;
    int borrow = 0;

    std::string num1 = this->sToStr();
    std::string num2 = other.sToStr();
    int len1 = num1.size();
    int len2 = num2.size();
    std::vector<int> result(len1 + len2, 0);

    for (int i = len1 - 1; i >= 0; i--)
    {
        for (int j = len2 - 1; j >= 0; j--)
        {
            int product = (num1[i] - '0') * (num2[j] - '0');//ASCII
            int sum = product + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }
    while (!result.empty() && result[0] == 0)
    {
        result.erase(result.begin());
    }
    res.i_length = result.size();
    res.pi_table = new int[res.i_length];
    for (int k = 0; k < res.i_length; k++)
    {
        res.pi_table[k] = result.at(k);
    }
    return CNumber(res);
}

CNumber CNumber::operator/(CNumber &other) const
{
    CNumber copy, result, one;
    copy = *this;
    one = 1;
    result = 0;

    if (other == result)
        throw std::invalid_argument("Division by zero not allowed");

    while (copy > other || copy == other)
    {
        copy = copy - other;
        result = result + one;
    }

    return result;
}

bool CNumber::operator==(CNumber &other)
{

    if (this->i_length != other.i_length)
        return false;
    else
    {
        for (int i = 0; i < this->i_length; ++i)
        {
            if (this->pi_table[i] != other.pi_table[i])
                return false;
        }
    }
    return true;
}

bool CNumber::operator>(CNumber &other)
{
    if (this->i_length == other.i_length)
    {
        for (int i = 0; i < this->i_length; ++i)
        {
            if (this->pi_table[i] > other.pi_table[i])
                return true;
            else if (this->pi_table[i] != other.pi_table[i])
                return false;
        }
    }
    else
        return this->i_length > other.i_length;
    return false;
}

std::string CNumber::sToStr() const
{
    std::stringstream ss;
    for (int i = 0; i < i_length; i++)
    {
        ss << pi_table[i];
    }
    return ss.str();
}

int CNumber::getLength() const
{
    return this->i_length;
}

const int *CNumber::getTable() const
{
    return this->pi_table;
}

const std::string CNumber::subtractLargeNumbers(std::string num1, std::string num2)
{
    std::string result;
    int borrow = 0;

    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0)
    {
        int x = (i >= 0) ? num1[i] - '0' : 0;
        int y = (j >= 0) ? num2[j] - '0' : 0;

        int diff = x - y - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result = std::to_string(diff) + result;

        i--;
        j--;
    }

    // Usuń wiodące zera z wyniku, jeśli istnieją
    // result.erase(0, result.find_first_not_of('0'));

    if (result.empty())
    {
        return "0";
    }

    // Jeśli wynik jest ujemny, dodaj znak minus
    if (borrow == 1)
    {
        result = "-" + subtractLargeNumbers(num2, num1);
    }

    return result;
}

CNumber& CNumber::operator>=(CNumber &other){
    if (&other == this)
    {
        return other;
    }

    if (other.pi_table)
    {
        delete[] other.pi_table;
    }

    other.i_length = this->i_length;

    if (other.i_length > 0)
    {
        other.pi_table = new int[other.i_length];
        for (int i = 0; i < other.i_length; i++)
        {
            other.pi_table[i] = this->pi_table[i];
        }
    }

    return (other);
}



