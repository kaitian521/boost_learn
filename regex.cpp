#include <iostream>
#include <assert.h>
#include <boost/regex.hpp>

using namespace std;

bool validate_card_format(const std::string& s)
{
   static const boost::regex e("(\\d{4}[- ]){3}\\d{4}");
   return regex_match(s, e);
}

int main()
{
    assert(validate_card_format("0123 2344-1232-3233"));
    assert(!validate_card_format("0123 29344-1232-3233"));
    return 0;
}
