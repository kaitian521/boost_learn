#include <iostream>
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
using namespace std;
using boost::bind;
using boost::any;

int f(int a, int b)
{
    return a + b;
}
int g(int a, int b)
{
    return a - b;
}
void p(int a)
{
    cout << a << endl;
}

struct node
{
   int operator()(int x, int y)
   {
       return x + y;
   }
   long long operator()(long long x, long long y)
   {
       return x - y;
   }
   long long operator()(long long x, int y)
   {
       return x * y;
   }
};
node nn;

int main()
{
    p(bind(f, 1, 2)());  
    p(bind(g, 1, 2)());  
    p(bind(g, _1, 2)(3));  
    int x = 1, y = 2;
    long long z = 3, zz = 4;
    p(bind<int>(nn, x, y)());
    p(bind<long long>(nn, z, zz)());
    //p(bind<long long, int>(nn, z, y)());
    boost::function<int ()> ff = bind(f, 1, 222);
    p(ff());
    return 0;
}
