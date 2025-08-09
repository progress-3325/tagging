#pragma once
#include <string_view>

namespace std
{

    /// @brief The tag class is usually used as a static constexpr in a class, once you have it there you can check it through various compile-time operations such as concepts
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
