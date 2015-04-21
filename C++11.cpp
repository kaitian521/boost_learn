#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>
#include <thread>
#include <algorithm>
#include <ctime>
#include <system_error>
#include <unistd.h>
#include <mutex>
#include <type_traits>

using namespace std;

void test_start_pointer() {
    std::unique_ptr<int> p1(new int(123));
    //std::unique_ptr<int> p2 = p1; //Not Allowed
    //std::unique_ptr<int> p3(p1);  //Not Allowed
    cout << *p1.get() << endl;

    std::unique_ptr<int>p4 = std::move(p1);

    cout << *p4 <<endl;
    //cout << *p1 << endl; //  crash
    p4 = nullptr;
    // p4 = new int(321);   //Not allowed
}

void test_new_init() {

    int *a = new int[4] {2, 1, 4, 3};

    vector<double> v{1.0, 33, 323};
}

// return value pick up .
template<typename T1, typename T2>
auto _auto1(T1 t1, T2 t2) -> decltype(t1 + t2) {
    auto ret = t1 + t2;
    return ret;
}

/*   Not Allowed : error: 't1' was not declared in this scope|
template<typename T1, typename T2>
decltype(t1 + t2) _auto2(T1 t1, T2 t2) {
    auto ret = t1 + t2;
    return ret;
}*/


template<typename T1, typename T2>
decltype(T1(0) * T2(0)) _auto3(T1 t1, T2 t2) {
    auto ret = t1 * t2;
    return ret;
}

void test_auto() {
    auto i = 3455;
    auto j = &i;
    auto k = std::ref(j);

    cout << *j << endl;
    cout << *k <<endl;

    cout << _auto1<double, int>(2.3, 2) << endl;
    cout << _auto3<double, long long>(12.45, 22) << endl;
}

void test_decltype() {
    int j = 345;
    int &k = j;
    const int &n = j;

//  'i4' declared as reference but not initialized|
    decltype(n) i1 = j; // const int&
    decltype(j) i2; // int
    decltype(k) i3 = j; // int &
    decltype((j)) i4 = j; // int &
}

void test_except() noexcept {
    cout << "No except" << endl;
}

class A {
public:
    int a = 0;
    double b = 1111.123;
    string c = "init";
};

class MyString {
public:
    int len = 0;
    char*data = nullptr;
    MyString() {}
    MyString(const char *p) {
        len = strlen(p);
        data = new char[len + 1];
        strcpy(data, p);
        data[len] = 0;
    }
    MyString(const MyString& t) {
        len = t.len;
        data = new char[len + 1];
        strcpy(data, t.data);
        cout << "Copy Construction called" << endl;
        data[len] = 0;
    }

    MyString(MyString&& t) {
        len = t.len;
        data = t.data;
        cout << "Copy Move Construction called" << endl;
        t.len = 0;
        t.data = nullptr;
    }

    MyString& operator=(const MyString& t) {
        if (this != &t) {
            len = t.len;
            data = new char[len + 1];
            strcpy(data, t.data);
            cout << "Copy Assignment called" << endl;
            data[len] = 0;
        }
        return *this;
    }

    MyString& operator=(MyString&& t) {
        if (this != &t) {
            len = t.len;
            data = t.data;
            cout << "Copy Move Assignment called" << endl;
            t.len = 0;
            t.data = nullptr;
        }
        return *this;
    }

    virtual ~MyString() {
        if (data) delete data;
        len = 0;
    }
    void print() {
        if (data) {
            cout << data << endl;
        }
        else {
            cout << "No data" << endl;
        }
    }
};

void test_inclass_init() {
    A a;
    cout << a.a << " " << a.b << " " << a.c << endl;
}

void test_STL_loop() {
    vector<int> v{9,8,7,6,5,4,3,2,1};
    for (int t: v) {
        cout << t << " ";
    }
    cout << endl;
    for (int &t: v) {
        t = 10 - t;
    }
    for (auto t: v) {
        cout << t << " ";
    }
    cout << endl;
}

void test_unordered_map() {
}

void print_value(int &x) {
    cout << "Lvalue is " << x << endl;
    x = 4;
}
void print_value(int &&x) {
    cout << "Rvalue is " << x << endl;
    x = 5;
}

void test_right_ref() {
    const int &a = 1;
    cout << a << endl;

    double tc = 2.5;
    double && rd1 = 1;
    int &&rd2 = 2;
    double && rd3 = tc + rd2 * 123;

    print_value(rd2);
    print_value(1002);

    MyString str1, str2;
    MyString str3("12345");
    str1 = MyString("I love u");
    //str2 = std::move(str2);   // force move

    str1.print();

    std::vector<MyString> vec;
    vec.push_back(MyString("wocao"));
}

int MOD = 19;
int count1 = 0;
bool f3(int x) {return x % MOD == 0;}

void test_lambda() {
    vector<int>v(1000);
    std::generate(v.begin(), v.end(), std::rand);
    int ret = count_if(v.begin(), v.end(), f3);
    cout << ret << endl;
    for_each(v.begin(), v.end(), [MOD,&count1](int x){count1 += (x % MOD == 0);} );
    cout << "wocao:" << count1 << endl;

    auto ff = [=]() -> int{return std::accumulate(v.begin(), v.end(), 0);};
    cout << "ff:============================= " << ff() << endl;
}

/*
void cb() {
    std::cout << "thread begin!" << std::endl;
}*/

void cb(int &id) {
    std::cout << "thread #" << std::this_thread::get_id() << " begin!" << std::endl;
    id = 6;

    sleep(1);
}
/*
void cb(int &id) {
    id = 1000;
    std::cout << "thread #" << id << " begin!" << std::endl;
}*/




void test_thread() {
    int n = 5;
    std::thread t(cb, std::ref(n));
    sleep(1);
    cout << t.get_id() << endl;
    t.join();
}

volatile int counter(0);
std::mutex mtx;

void Add() {
    mtx.lock();
    for (int i = 0; i < 10000000; i++)
        ++counter;
    mtx.unlock();

    {
        std::lock_guard<std::mutex> lck(mtx);
        for (int i = 0; i < 10000000; i++)
            ++counter;
    }
}

void test_mutex() {
    cout << "mutex test" << endl;
    std::thread t[5];
    for (int i = 0; i < 5; i++) {
        t[i] = std::thread(Add);
    }
    for (int i = 0; i < 5; i++) {
        t[i].join();
    }
    cout << counter << endl;
}

void test_condition_and_chrono_regex() {
}

void test_minmax() {
    vector<int> v{3, 12 ,0, 34, 12, 23};
    auto ret = std::minmax(1, 3);
    cout << ret.first << " " << ret.second << endl;

    auto ret1 = std::minmax_element(v.begin(), v.end());
    cout << *ret1.first << " " << *ret1.second << endl;
}

class B {
public:
    int f(int &x, int &y) {
        x = 13;
        return x * y;
    }
};

void test_bind() {

    B *b = new B;
    int x = 12, y = 13;
    auto fff = std::bind(&B::f, b, x, y);
    cout << fff() << " " << x << endl;
    auto ffff = std::bind(&B::f, b, std::ref(x), y);
    cout << ffff() << endl;
    cout << x << endl;
}

void test_to_string() {
    string s = std::to_string(100000.12345);
    s = std::to_string(char('a'));
    cout << s << endl;
}

int main()
{
    test_start_pointer();
    test_new_init();

    test_auto();
    test_decltype();

    test_except();

    test_inclass_init();

    test_STL_loop();

    test_unordered_map();

    test_right_ref();

    test_lambda();

    test_thread();

    test_mutex();

    test_condition_and_chrono_regex();

    test_minmax();

    test_bind();

    test_to_string();
    return 0;
}
