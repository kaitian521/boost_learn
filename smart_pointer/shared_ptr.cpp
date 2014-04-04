#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <boost/smart_ptr.hpp>
#include <boost/any.hpp>
#include <algorithm>
using boost::shared_ptr;

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

int print(shared_ptr<Simple> sp)
{
    std::cout << sp.use_count() << std::endl;    
    return sp.use_count();
}

int print(shared_ptr<int> sp)
{
    std::cout << sp.use_count() << std::endl;    
    return sp.use_count();
}
void f(boost::any &any)
{
     //std::cout << any;
}

int main()
{
    shared_ptr<Simple> sp1(new Simple("Haha", 10));
    assert(print(sp1) == 2);
    shared_ptr<Simple> sp2(sp1);
    assert(print(sp2) == 3);
    shared_ptr<Simple> sp3 = sp2;
    assert(print(sp3) == 4);
    sp1->str += "You";
    sp2->print();
    std::vector<boost::any>v;
    shared_ptr<int> spt1(new int(500));
    v.push_back(sp1);
    v.push_back(sp2);
    v.push_back(sp3);
    v.push_back(spt1);
    std::for_each(v.begin(), v.end(), f);    
    assert(print(sp3) == 7);
    v.erase(v.begin());
    assert(print(sp3) == 6);
    v[0] = spt1;
    assert(print(sp3) == 5);
    (print(spt1) == 4);
    return 0;
}
