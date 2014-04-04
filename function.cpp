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
   int check(int x)
   {
       return x > 0;
   }
};
node nn;

int main()
{
    boost::function<int(int, int)>ff = f;
    p(f(1, 2));
    boost::function<int(node*, int)>gg = &node::check;
    p(gg(&nn, -2));
    return 0;
}
