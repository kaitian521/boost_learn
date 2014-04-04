#include <iostream>
#include <boost/functional/hash.hpp>
#include <boost/unordered_set.hpp>
#include <boost/foreach.hpp>
#include <string>

using namespace std;

namespace lib{
struct book
{
    int id;
    string author;
    string title;
    book(int _id, string _author, string _title)
    {
        id = _id;
        author = _author;
        title = _title;
    }
};

bool operator==(const book& a, const book& b)
{
    return a.id == b.id;
}

std::size_t hash_value(book const&a)
{
    boost::hash<int>hasher;
    return hasher(a.id);
}
}
int main()
{
    boost::hash<string> string_hash;
    cout << string_hash("WO CAO") << endl; 
    boost::hash< vector<int> > vector_hash;
    int a[3] = {2,3,1};
    vector<int>v(a, a + 3);
    cout << vector_hash(v) << endl; 
    
    lib::book knife(3458, "Zane Grey", "The Hash Knife Outfit"); 
    lib::book danger(1354, "Paul J. Shanley", "HAHAHAHAHAH"); 
    boost::hash< lib::book >hasher;
    cout << hasher(knife) << "\t" << hasher(danger) << endl;

    boost::unordered_set< lib::book > oset;
    oset.insert(knife);
    oset.insert(danger);
    oset.insert(lib::book(123, "London", "Strong Man")); 
    
    BOOST_FOREACH(lib::book book, oset)
    {
        cout << book.id << "\t" << book.author << "\t" << book.title << endl;
    }
    return 0;
}
