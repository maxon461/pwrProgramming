#include <iostream>
#include "CNumber.h"
std::ostream &operator<<(std::ostream &os, CNumber &obj)
{
    os << "[ ";
    if (obj.getLength() > 0)
    {
        os << obj.getTable()[0];
        for (int i = 1; i < obj.getLength(); i++)
        {
            os << ", " << obj.getTable()[i];
        }
    }
    return os << " ]";
}
CNumber &operator>=(int val, CNumber &obj)
{
    obj = val;
    return obj;
}

int &operator>=(CNumber obj, int &val)
{
    val = std::stoi(obj.sToStr());
    return val;
}

int main()
{
    CNumber c_num_0, c_num_1;
    c_num_0 = 1881;
    c_num_1 = 19;
    int x = 4;
    int temp = 0;

    312 >= c_num_1 >= temp >= c_num_1 >= c_num_0;
    std::cout << c_num_0.sToStr() << std::endl;

    c_num_0 = c_num_1;
    std::string str = c_num_0.sToStr();
    std::cout << str;
    std::cout << c_num_0;

    //Operator +
    CNumber c_num_2 = c_num_0 + c_num_1;
    std::cout << "Result of + : " << c_num_2.sToStr() << std::endl; // GJ!
    //Operator -
    CNumber c_num_3 = c_num_0 - c_num_1;
    std::cout << " Result of - : " << c_num_3.sToStr() << std::endl; // GJ!
    //Operator *
    CNumber c_num_4 = c_num_0 * c_num_1;
    std::cout << " Result of * : " << c_num_4.sToStr() << std::endl; // GJ!
    //Operator /
    CNumber c_num_5 = c_num_0 / c_num_1;
    std::cout << " Result of / : " << c_num_5.sToStr() << std::endl; // GJ!

    return 0;
}
