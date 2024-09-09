#ifndef __MISERVER_STRSPLIT_HPP
#define __MISERVER_STRSPLIT_HPP
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
namespace mimp
{
    namespace util
    {
        std::vector<std::string> strsplit(const char *__cp, const int __sz, char __dc)
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
    }
}

#endif