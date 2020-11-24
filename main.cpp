#include <iostream>
#include <boost/container/vector.hpp>

int main(int argc, char* argv[])
{
    using boost::container::vector;

    vector<int> v = { 1, 2, 3 };
    v[0] = 2;
    std::cout << v[0] << std::endl;

    return 0;
}
