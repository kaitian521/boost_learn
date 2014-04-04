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
    Simple(std::string _str, int _value): str(_str), value(_value)
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
    boost::scoped_ptr<Simple> p1( new Simple("", 1) );
    if (p1.get())
    {
        p1->print();
        p1.get()->str += "Hello World";
        p1->print();
        (*p1).str += " woca";
        p1->print();

        /*
         scoped_ptr(scoped_ptr const &);
         scoped_ptr & operator=(scoped_ptr const &);

         This two funcitons are private, should not be used
        */
        //boost::scoped_ptr<Simple>p2(p1);
        //p2->print();
    } 
    else
    {
        std::cout << "Wrong!";
    }
    return 0;
}
