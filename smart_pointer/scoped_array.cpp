#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <boost/smart_ptr.hpp>

class Simple
{
public:
    int value;
    std::string str;
    Simple(std::string _str = "", int _value = 0): str(_str), value(_value)
    {
        std::cout << "Simple Construction" << std::endl;
    }
    ~Simple()
    {
        std::cout << "Simple Deonstruction" << std::endl;
    }
    void print()
    {
        std::cout << "Simple: " << str << std::endl;
    }
};

int main()
{
    boost::scoped_array<Simple> p1( new Simple[10] );
    if (p1)
    {
        p1[0].print();
        p1[0].str += "Hello World";
        p1[0].print();
        (p1[0]).str += " woca";
        p1[0].print();
    } 
    else
    {
        std::cout << "Wrong!";
    }
    return 0;
}
