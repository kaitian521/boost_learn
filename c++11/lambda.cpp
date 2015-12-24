#include <iostream>
#include <functional>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

class T {
public:
	int count;
	void f() {
		auto arr = {1, 2, 3, 4, 6};
		for_each(arr.begin(), arr.end(), [this](int x){
			count += x;
			cout << count << endl;
		});
	}
};

int main() {
	int count = 0;
	auto arr = {1, 2, 3, 4, 6};
	for_each(arr.begin(), arr.end(), [&count](int x){
			cout << x << endl;
			count += x;
			});
	cout << count << endl;

	//T t;
	//t.f();
	auto my_lambda_func = [&](int x) { /*...*/ };
	function<void(int)> func1 = [&](int x) { /*...*/ };
	auto my_onheap_lambda_func = new auto([=](int x) { /*...*/ });

	auto a_lambda_func = [](int x) { cout << x * x << endl; };
	void (* func_ptr)(int) = a_lambda_func;
	func_ptr(4); //calls the lambda.

	return 0;
}
