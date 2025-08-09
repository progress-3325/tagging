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
        consteval tag(const tag& other) : id(other.get_id()) {}
        consteval string_view get_id() const {return id;}
        consteval tag& operator=(const tag& other)
        {
            this->id = other.get_id();
            return *this;
        }
        consteval bool operator==(const char* c) const
        {
            return id == c;
        }
    };
}
