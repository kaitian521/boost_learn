#include <iostream>
#include <vector>
#include <boost/assign.hpp>
using namespace std;
using namespace boost::assign;
int main()
{
    vector<int>v;
    v += 1,2,3,4,5;
    cout << v.size() << endl;
    return 0;
}
