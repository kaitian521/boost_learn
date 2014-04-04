#include <iostream>
#include <boost/random.hpp>

using namespace std;

int main()
{
    boost::random::mt19937 rng;     // produces randomness out of thin air
                                    // see pseudo-random number generators
    boost::random::uniform_int_distribution<> six(1,6);
                                    // distribution that maps to 1..6
                                    // see random number distributions
    cout <<six(rng) << endl;;       // simulate rolling a die

    double probabilities[] = {
    0.5, 0.1, 0.1, 0.1, 0.1, 0.1
    };
    boost::random::discrete_distribution<> dist(probabilities);
    for (int i = 0; i < 10; i++) cout << dist(rng) << endl;

    boost::random::uniform_smallint<>si(1, 100);
    for (int i = 0; i < 10; i++) cout << si(rng) << endl;
   
    boost::random::uniform_01<>uniform;
    for (int i = 0; i < 10; i++) cout << uniform(rng) << endl;

    boost::random::uniform_real_distribution<>rd(0.1, 0.6);
    for (int i = 0; i < 10; i++) cout << rd(rng) << endl;
    return 0;
}
