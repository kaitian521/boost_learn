#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/foreach.hpp>
using namespace std;

struct node
{
    void operator() (int x)
    {
        cout << x << endl;
    }
};

void print(int x)
{
    cout << x << endl;
}
int main()
{
    int a[10] = {1, 3, 5};
    vector <int>v(a, a + 3);
    for_each(v.begin(), v.end(), print);
    for_each(v.begin(), v.end(), node());
    BOOST_FOREACH(int x, v)
    {
        print(x);
    }
    BOOST_REVERSE_FOREACH(int x, v)
    {
        print(x);
    }
    BOOST_FOREACH(int &x, a)
    {
        x += 1;
        if (x == 3) break;
    }
    BOOST_FOREACH(int &x, a)
    {
        print(x);
    }
    return 0;
}
