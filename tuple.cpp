#include <iostream>
#include <assert.h>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

using namespace std;
using boost::tuple;
using namespace boost;

class X
{
    string x;
public:
    X(): x(string("")) {};
    X(string _x): x(_x) {};
};

void test_base()
{
    tuple<int, double>t1();
    tuple<int, double>t2(1);
    tuple<int, double>t3(1, 3.14); 

    tuple<X, X>t4();
    tuple<X, X>t5(string("Hello "), string("World."));
}

void test_ref()
{
    double d = 5;
    tuple<double&> t1(d);

    tuple<const double&> t2(d);
    tuple<const double&> t3(d + 0.6);
}

void test_copy()
{
    int a[10];
    //tuple<int [10], int> t1(a, 5);
    tuple<int [10], int> t1();
}

tuple<int, int, double>
add_multiply_divide(int a, int b)
{
    return make_tuple(a+b, a*b, double(a)/double(b));
}

tuple<int, int> foo(const int&a, int b)
{
   return make_tuple(a, b);
}

tuple<string, int>
bar()
{
   int x = 5;
   return make_tuple(string("Hello World"), x);
}

void test_make_tuple()
{
    tuple<int, int, double> t1 = add_multiply_divide(10.0, 3.0);
    int a = 4, b = 5;
    tuple<int, int> t2 = foo(a, b);

    tuple<string, int> t3 = bar();
}

void test_access()
{
    int a = 1;
    string b = "hello";
    double c = 3.14;

    tuple<int, string&, const double > t1(a, b, c);
    cout << t1 << endl;
    get<0>(t1) = 5;
    cout << get<0>(t1) << endl;
}

void test_relation()
{
    tuple<std::string, int> t1(std::string("same?"), 2);
    tuple<std::string, long> t2(std::string("same?"), 2);
    tuple<std::string, long> t3(std::string("different"), 3);
    assert(t1 == t2);
    assert(t1 != t3);
}

void test_tie()
{
    int x = 1;
    double y = 3.14;
    tuple<int&, double &> t1 = make_tuple(ref(x), ref(y));
    get<0>(t1) = 5;
    get<1>(t1) = 4.56;
    cout << get<0>(t1) << endl;
    cout << get<1>(t1) << endl;

    tie(x, y) = make_tuple(10, 234.5);
    cout << x << "\t" << y << endl;
}

int main()
{
    test_base();
    test_ref();
    test_copy();

    test_make_tuple();

    test_access();
    test_relation();
    test_tie();
    return 0;
}
