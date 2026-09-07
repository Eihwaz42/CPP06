#include "Base.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    Base *object;

    std::srand(std::time(NULL));

    for (int i = 0; i < 10; i++)
    {
        object = generate();

        std::cout << "Pointer identification:   ";
        identify(object); // pointeur

        std::cout << "Reference identification: ";
        identify(*object); // reference

        std::cout << std::endl;

        delete object;
    }

    return 0;
}