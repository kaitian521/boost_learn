#include <iostream>
#include <boost/lambda/bind.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <vector>
#include <algorithm>
#include <boost/assign.hpp>
#include <string>
using namespace std;
using namespace boost::assign;
using namespace boost::lambda;

int g(int x)
{
    return 2 * x;
}
int main()
{
    int a[4] = {1,2,3,4};
    vector<int>v(a, a + 4);
    v += 3,4,5,6;
    std::sort(v.begin(), v.end(), _1 <= _2);
    std::for_each(v.begin(), v.end(), (cout << _1 << '\n'));

    boost::function<void(int, string)> f = 
    (cout << _1 << "\t" << _2 << "\n");
    f(2, "haha");
    std::for_each(v.begin(), v.end(), if_then(_1 % 3 == 0, cout << _1 << '\n'));
    std::for_each(v.begin(), v.end(), if_then_else(_1 % 3 == 0, _1 = -1, _1 = -2));
    std::for_each(v.begin(), v.end(), _1 = bind(g, _1));
    std::for_each(v.begin(), v.end(), (cout << _1 << '\n'));
    return 0;
}
