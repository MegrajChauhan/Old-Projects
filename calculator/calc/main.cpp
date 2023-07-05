#include <iostream>
#include "API.hpp"

int main()
{
    while (true)
    {
        std::string in;
        std::cout << ">>>";
        std::getline(std::cin, in);
        API a(in);
        a.eval();
        std::cout << a.get_res() << std::endl;
    }
}
