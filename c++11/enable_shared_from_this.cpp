#include <vector>
#include <memory>
#include <iostream>


class S {
public:	
	std::shared_ptr<S> get() {
		return std::shared_ptr<S>(this);
	}
	S() {
		s = new char[100];
		std::cout << "constructed" << std::endl;
	}
	~ S() {
		delete [] s;
		std::cout << "destructed" << std::endl;
	}

private:
	char *s;
};

class T: public std::enable_shared_from_this<T> {
public:	
	std::shared_ptr<T> get() {
		return shared_from_this();
	}
	T() {
		s = new char[100];
		std::cout << "constructed" << std::endl;
	}
	~ T() {
		delete [] s;
		std::cout << "destructed" << std::endl;
	}

private:
	char *s;
};

int main() {
	using namespace std;

	/*S *s = new S();
	shared_ptr<S> _p1(s);
	shared_ptr<S> _p2(s);*/

	/*shared_ptr<S>p(new S());
	shared_ptr<S>p2 = p->get();
	cout << "use_count = " << p.use_count() << endl;*/


	shared_ptr<T> t(new T());
	auto t2 = t->get();
	
	return 0;
}
