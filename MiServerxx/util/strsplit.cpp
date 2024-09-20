#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <MiServerxx/util/strsplit.hpp>

std::vector<std::string> mimp::util::strsplit(const char *__cp, const int __sz, char __dc)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(__cp);
    while (std::getline(tokenStream, token, __dc))
    {
        tokens.push_back(token);
    }
    return tokens;
}