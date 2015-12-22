#include <vector>
#include <iostream>
#include <memory>

class Song {
private:
	std::string title, singer;
public:	
	Song(std::string t, std::string s): title(t), singer(s) {
		using namespace std;
		cout << "Song class constructed" << endl;
	}
	~ Song() {
		using namespace std;
		cout << "Song class destructed" << endl;
	}
	void print() {
		using namespace std;
		cout << "title = " << title << ", singer = " << singer <<endl;
	}
};


void init() {
	using namespace std;
	auto p = make_shared<Song>("Love", "Westlife");
	shared_ptr<Song> p1(new Song("1", "2"));

	p->print();
	p1->print();

	p1 = p;
	cout << "use_count = " << p1.use_count() << endl;

	auto p2(p);
	cout << "use_count = " << p2.use_count() << endl;

	p = nullptr;
	cout << "use_count = " << p2.use_count() << endl;
}

void test_vector() {
	using namespace std;
	cout << "===================" << endl;
	vector<shared_ptr<Song>> songs;
	songs.push_back(make_shared<Song>("1", "2"));
	songs.push_back(std::shared_ptr<Song>(new Song("3", "4")));

	for (auto &p: songs) {
		cout << "use_count = " << p.use_count() << endl;
		p->print();
	}

}

int main() {

	init();
	test_vector();

	return 0;
}
