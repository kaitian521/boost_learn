#include <iostream>
#include <boost/array.hpp>

using boost::array;
using namespace std;

int main()
{
    array<int, 100>a = {1, 3, 4};
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << endl;
    }
    return 0;
}
