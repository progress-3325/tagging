#pragma once
#include <string_view>

namespace std
{

    class tag
    {
        struct tag_id
        {
            constexpr string_view id;
            consteval tag_id(const char* c) : id(c) {}
        };
        constexpr tag_id id("tag");
    public:
        consteval tag(const char* c) : id(c) {}
        consteval bool operator==(const char* c) const
        {
            return id.id == c;
        }
    };
}
