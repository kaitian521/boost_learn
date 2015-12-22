#include <iostream>
#include <vector>
using namespace std;

struct A {
	int x;
	double y;
};

struct B {
	int x;
	A y[2];
};

class SequenceClass {
public:
    SequenceClass(std::initializer_list<int> list): v(list) {
		cout << "construction called" << endl;
	};
	void append(std::initializer_list<int> list) {
		v.insert(v.end(), list.begin(), list.end());
	}

public:
	std::vector<int> v;
};

struct BasicStruct {
    int x;
    double y;
};

struct AltStruct {
    AltStruct(int x, double y) : x_{x}, y_{y} {}
private:
    int x_;
    double y_;
};

BasicStruct var1{5, 3.2};
AltStruct var2{2, 4.3};
//BasicStruct var11(5, 3.2);
AltStruct var22{2, 4.3};


struct IdString {
	    std::string name;
		    int identifier;
};

IdString get_string() {
	    return {"foo", 42}; //Note the lack of explicit type.
}


int main() {
	A a = {1, 1.2};
	A b[3] = {{1, 2.8}, {3, 4.5}, {5, 6.0}};
	B aa = {1, {{2, 3}, {3,4}} };

	SequenceClass s = {1, 2, 4, 3};
	for (auto &x: s.v) {
		cout << x << " ";
	}
	s.append({5, 6, 7, 8});
	cout << endl;
	for (auto &x: s.v) {
		cout << x << " ";
	}
	cout << endl;

	for (auto &x: {12, 13, 14}) {
		cout << x << " ";
	}
	cout << endl;

	cout << get_string().name << " " << get_string(). identifier <<endl;

	vector<int> vv{4};
	cout << "v.size() = " << vv.size() << endl;

	return 0;
}
