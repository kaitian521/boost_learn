#include <iostream>
#include <string>
#include <assert.h>
#include <string.h>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

using namespace std;

void test_nil()
{
    boost::uuids::uuid ng = boost::uuids::nil_uuid();
    assert(ng.is_nil());
}

void p(boost::uuids::uuid id)
{
    //cout << id << endl;
    //string s = boost::lexical_cast<string>(id);
    cout << to_string(id) << endl;
}
void test_string_generate()
{
    boost::uuids::string_generator gen;
    boost::uuids::uuid u1 = gen("{01234567-89ab-cdef-0123-456789abcdef}");
    boost::uuids::uuid u2 = gen(L"01234567-89ab-cdef-0123-456789abcdef");
    boost::uuids::uuid u3 = gen(std::string("1123456d89dbcdef0123456789abcdef"));
    boost::uuids::uuid u4 = gen(std::wstring(L"01234567-89ab-cdef-0123-456789abcdef"));
    p(u1);
    p(u2);
    p(u3);
    p(u4);
}

void test_name()
{
    boost::uuids::uuid dns_namespace_uuid; // initialize to {6ba7b810-9dad-11d1-80b4-00c04fd430c8}

    boost::uuids::name_generator gen(dns_namespace_uuid);
    boost::uuids::uuid u1 = gen("boost.org");
    p(u1);
    boost::uuids::uuid u2 = gen("baidu.com");
    p(u2);
}

void test_random()
{
    //default construct the random number generator and seed it
    boost::uuids::basic_random_generator<boost::mt19937> gen;
    boost::uuids::uuid u1 = gen();
    p(u1);
    boost::uuids::uuid u2 = gen();
    p(u2);
    
}
int main()
{
    boost::uuids::uuid u;
    char s[17] = "abcdefghijklmnop";
    memcpy(&u, s, 15);
    p(u);
    cout << u.size() << endl;
    memset(&u, 0, sizeof(u));
    assert(u.is_nil());

    test_nil();
    test_string_generate();
    test_name();
    test_random();
    return 0;
}
