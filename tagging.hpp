#pragma once
#include <string_view>

namespace std
{

    class tag
    {
        constexpr string_view id;
    public:
        consteval tag(const char* c) : id(c) {}
        consteval bool operator==(const char* c) const
        {
            return id == c;
        }
    };
}
