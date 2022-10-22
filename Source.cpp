#include "sha256.h"
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>

using std::string;
using std::endl;

void FileGenerator(int n) {
    SHA256 sha256;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(100, 1000000);
    std::ofstream fr("users.txt");
    std::stringstream my_buffer;
    string vardas;
    string s1, s2, s;
    for (int i = 0; i < n; i++) {
        vardas = "Vartotojas" + std::to_string(i + 1);
        my_buffer << vardas + " " << sha256(vardas) << " " << distribution(generator);
        if (i + 1 != n) my_buffer << endl;
    }
    fr << my_buffer.str();
    fr.close();
}

int main()
{
    FileGenerator(1000);
    return 0;
}