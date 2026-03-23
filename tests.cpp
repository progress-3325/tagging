#include "tagging.h"


template<typename T>
	requires std::is_same_v<T, unsigned char> || std::is_same_v<T, unsigned short> || std::is_same_v<T, unsigned int> || std::is_same_v<T, unsigned long> || std::is_same_v<T, unsigned long long>
void natural_only(T);
template<typename T>
	requires std::is_same_v<T, unsigned char> || std::is_same_v<T, unsigned short> || std::is_same_v<T, unsigned int> || std::is_same_v<T, unsigned long> || std::is_same_v<T, unsigned long long> || std::is_same_v<T, char> || std::is_same_v<T, short> || std::is_same_v<T, int> || std::is_same_v<T, long> || std::is_same_v<T, long long>
void whole_only(T);

using natural_numbers = tag::merge_tags_and_types_t<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;
using whole_numbers   = tag::merge_tags_and_types_t<signed char, short, int, long, long long, natural_numbers>;
using real_numbers    = tag::merge_tags_and_types_t<float, double, long double>;
using numbers         = tag::merge_tags_and_types_t<whole_numbers, real_numbers>;

template<typename T>
concept is_number = tag::contains<numbers, T>;

template<typename T>
concept is_whole = tag::contains<whole_numbers, T>;

template<typename T>
concept is_natural = tag::contains<natural_numbers, T>;

template<typename T>
concept is_real = tag::contains<real_numbers, T>;

template<typename T>
	requires tag::contains<natural_numbers, T>
void natural_only(T);

int main()
{
	return 0;
}
