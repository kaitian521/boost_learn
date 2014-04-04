#include <iostream>
#include <boost/pool/pool.hpp>
using namespace std;

void f_pool()
{
    boost::pool<> p( sizeof(int) );
    for (int i = 0; i < 1000000; i++)
    {
        int *t = (int*)p.malloc();
        p.free(t);
    }
}

int main()
{
    f_pool(); 
    return 0;
}
