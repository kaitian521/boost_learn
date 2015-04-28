#include <iostream>
#include "boost/any.hpp"
using namespace std;
using boost::any;
using boost::any_cast;

int main()
{
    any a(0);
    cout << any_cast<int>(a) << ": " << a.type().name() << endl;
    any b(string("hello"));
    cout << any_cast<string>(b) << ": " << b.type().name() << endl;
    any c('A');
    cout << any_cast<char>(c) << ": " << c.type().name() << endl;
    c = b;
    cout << any_cast<string>(c) << ": " << c.type().name() << endl;
    try
    {
        any_cast<char>(c);
    }
    catch (boost::bad_any_cast& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
