#include <iostream>
#include <string>
#include <stdio.h>

class U_ptr
{
friend class HasPtr;
private:
    int use;
    int *ip;
    U_ptr(int *_ip): use(1), ip(_ip)
    {
        std::cout << "U_ptr Construction" << std::endl;
    }
    ~U_ptr()
    {
        delete ip;
        std::cout << "U_ptr Destruction" << std::endl;
    }
};

class HasPtr
{
    int value;
    U_ptr *ptr;

public:
    HasPtr(int *p, int _value = 0): ptr(new U_ptr(p)), value(_value)
    {
        std::cout << "HasPtr Construction" << std::endl;
    }
    ~HasPtr()
    {
        std::cout << "HasPtr Destruction: " << ptr->use << std::endl;
        if (--ptr->use == 0)
        {
            delete ptr;
        }
    }
    HasPtr(const HasPtr & hp): ptr(hp.ptr), value(hp.value)
    {
        ++ptr->use;
        std::cout << "HasPtr Copy Construction: " << ptr->use << std::endl;
    }
    HasPtr & operator = (HasPtr &hp)
    {
        (hp.ptr)->use ++;
        if (-- ptr->use == 0)
        {
            delete ptr;
        }
        ptr = hp.ptr;
        value = hp.value;
        return *this;
    }

    int * get_ptr()
    {
        return ptr->ip;
    }
    int get_value()
    {
        return value;
    }
    void set_ptr(int *p)
    {
        ptr->ip = p;
    }
    void set_value(int _value)
    {
        value = _value;
    }
    int get_ptr_value()
    {
        return *(ptr->ip);
    }
    void set_ptr_value(int x)
    {
       *(ptr->ip) = x;
    }
};

int main()
{
    /*HasPtr p1(new int(12345));
    HasPtr p2(p1);
    HasPtr p3 = p2;*/
 
    HasPtr *pp1 = new HasPtr(new int(2345));
    HasPtr *pp2 = new HasPtr(*pp1);
    HasPtr *pp3 = new HasPtr(*pp2);
    HasPtr pp4 = *pp3;
    delete pp3; 
    delete pp1;
    delete pp2;
    return 0;
}
