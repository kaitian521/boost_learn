#include <memory>
#include <vector>
#include <iostream>

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

void do_print(std::unique_ptr<Song> p) {
	p->print();
}

std::unique_ptr<Song> getSong() {
	using namespace std;
	// return std::make_unique<Song>("you are beautiful", "Blunt"); since C++14 ... sigh...
	return std::unique_ptr<Song>(new Song("you are beautiful", "Blunt"));
}

void test_vector() {
	using namespace std;
    vector<unique_ptr<Song>> songs;

    // Create a few new unique_ptr<Song> instances
	// and add them to vector using implicit move semantics.
	songs.push_back(std::unique_ptr<Song>(new Song("B'z", "Juice")));
	songs.push_back(std::unique_ptr<Song>(new Song("Namie Amuro", "Funky Town")));
    // Pass by const reference when possible to avoid copying.
    for (const auto& song : songs)
    {
		song->print();
    }   
}

int main() {
	using namespace std;

	unique_ptr<Song> p(new Song("My Love", "WestLife"));
	p->print();
	//p.reset();


	do_print(std::move(p));

	p = getSong();
	p->print();

	test_vector();

	cout << "done ..." << endl;


	return 0;
}
