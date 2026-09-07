#include "Serializer.hpp"

#include <iostream>

int main()
{
    Data        data;
    Data        *original;
    uintptr_t   raw;
    Data        *result;

    data.id = 42;
    data.name = "Lisa";

    original = &data;
    raw = Serializer::serialize(original);
    result = Serializer::deserialize(raw);

    std::cout << "Original pointer:     "
              << original << std::endl;

    std::cout << "Serialized value:     "
              << raw << std::endl;

    std::cout << "Deserialized pointer: "
              << result << std::endl;

    std::cout << "ID:   "
              << result->id << std::endl;

    std::cout << "Name: "
              << result->name << std::endl;

    if (result == original)
        std::cout << "Success: pointers are equal"
                  << std::endl;
    else
        std::cout << "Error: pointers are different"
                  << std::endl;

    return 0;
}