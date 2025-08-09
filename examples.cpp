#include "tagging.hpp"

tag(natural_numbers, unsigned short, unsigned int, unsigned long, unsigned long long);
tag(whole_numbers, natural_numbers, short, int, long, long long);
tag(numbers, whole_numbers, float, double);
tag(char_types, char, unsigned char, signed char);
tag(raw_types, numbers, char_types, bool);

template<typename T>
concept is_number = contains<numbers, T>;
struct nums;

tag(ext_numbers, numbers, is_number);

template<typename T>
requires contains<ext_numbers, T>
bool is_num(const T& t)
{
    return true;
}