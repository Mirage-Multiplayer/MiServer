#ifndef __MISERVER_STRFORMAT_HPP
#define __MISERVER_STRFORMAT_HPP
#include <cstring>
#include <string>
namespace mimp
{
    namespace util
    {
        template <typename... Args>
        const char *strnformat(const char *__fmt, const int __sz, Args &&...args)
        {
            char *buf = new char[__sz];
            snprintf(buf, __sz, __fmt, std::forward<Args>(args)...);
            return buf;
        }
    }
}
#endif