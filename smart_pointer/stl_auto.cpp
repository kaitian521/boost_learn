#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>

using namespace std;

class Simple
{
public:
    int value;
    string str;
    Simple(string _str, int _value): str(_str), value(_value)
    {
        cout << "Simple Construction" << endl;
    }
    ~Simple()
    {
        cout << "Simple Deonstruction" << endl;
    }
    void print()
    {
        cout << "Simple: " << str << endl;
    }
};

int main()
{
    std::auto_ptr<Simple> p1( new Simple("", 1) );
    if (p1.get())
    {
        p1->print();
        p1.get()->str += "Hello World";
        p1->print();
        (*p1).str += " woca";
        p1->print();

        std::auto_ptr<Simple>p2;
        p2 = p1;
        p2->print();
        /***
          * never let two auto_ptr point to the same object
          * never use "operator =" in auth_ptr
          * do not use auto_ptr as parameter
          * do not put auto_ptr into vector
          * never use auto_ptr to store a array, because delete, should be delete []
        ***/
            
        //p1->print();
    } 
    else
    {
        cout << "Wrong!";
    }
    return 0;
}
