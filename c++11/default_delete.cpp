#include <iostream>

using namespace std;

class A {
	public:
		int x;
		A() = default;
		A(int x) {
			this->x = x;
		}
		A(const A& a) = delete;
};

int main() {
	A a;
	cout << a.x << endl;
	A b(a);
	return 0;
}
