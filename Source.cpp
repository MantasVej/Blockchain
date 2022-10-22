#include "sha256.h"
#include <iostream>
int main()
{
    SHA256 sha256;
    std::cout << sha256("Hello World") << std::endl;
    return 0;
}