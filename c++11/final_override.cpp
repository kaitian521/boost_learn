#include <iostream>
#include <string>

using namespace std;


class A {
public:	
	virtual void f(int x);
};

class B: public A {
public:	
	virtual void f(double x);
	//virtual void f(double x) override;
};

void A::f(int x) {
	 cout << "int" << endl;
}
void B::f(double x) {
	cout << "double" << endl;
}

/*class C final {
};

class D: public C {
};

class E {
	virtual void f() final;
};
void E::f() {
}

class F: public E {
	virtual void f() override;
};*/

int main() {
	A*p = new B();
	p->f(1);
	int final = 0;
	int override = final + 10;
	cout << final << " " << override <<endl;
	return 0;
}
