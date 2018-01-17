#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <random>
#include "effolkronium/random.hpp"

using namespace std;;
using Random = effolkronium::random_static;

int main()
{
    int temp=5;
    for(int ctr=1;ctr<=10;ctr++)
    {
        auto val = Random::get(1, temp);
        cout<<val<<endl;
    }
}
