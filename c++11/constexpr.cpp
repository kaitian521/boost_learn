#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#ifdef HAS_MOVE_SEMANTICS
constexpr double earth_gravitational_acceleration = 9.8;
constexpr double moon_gravitational_acceleration = earth_gravitational_acceleration / 6.0;
#else
const double earth_gravitational_acceleration = 9.8;
const double moon_gravitational_acceleration = earth_gravitational_acceleration / 6.0;
#endif

constexpr int multiply (int x, int y)
{
	return x * y;
}
// the compiler may evaluate this at compile time
const int val = multiply(10, 10 );

int my_array[ multiply(3 , 3) ];

constexpr int factorial (int n)
{
	return n > 0 ? n + factorial( n - 1 ) : 0;
}

class Circle {
	int x, y;
public:
	constexpr Circle(int _x, int _y): x(_x), y(_y) {}
public:
	constexpr double getArea() {
		return x * y * 3.1415;
	}
};

int main() {
	cout << earth_gravitational_acceleration << endl;
	cout << val << endl;
	cout << "my_array sizeof = " << sizeof(my_array) << endl;
	cout << "recursive factorial = " << factorial(100) << endl;
	cout << "recursive factorial = " << factorial(200) << endl;

	constexpr Circle circle(5, 9);
	constexpr double area = circle.getArea();
	cout << "the area of the circle = " << area << endl;

	// error: area = 56.1;
	const vector<int> v;
	vector<int> v2 = {1, 3, 5, 7, 0};
	//error v = v2;
	for (const int& val: v2) {
		((vector<int>)v).push_back(val);
	}
	for_each(v2.begin(), v2.end(), [v](const int &x) {cout << "val: " << x << endl;});

	const int size = 10;
	constexpr int size_expr = factorial(100);
	int arrr[size], arr2[size_expr];
	return 0;
}
