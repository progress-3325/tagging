#include "tagging.h"


template<typename T>
	requires std::is_same_v<T, unsigned char> || std::is_same_v<T, unsigned short> || std::is_same_v<T, unsigned int> || std::is_same_v<T, unsigned long> || std::is_same_v<T, unsigned long long>
void natural_only(T);
template<typename T>
	requires std::is_same_v<T, unsigned char> || std::is_same_v<T, unsigned short> || std::is_same_v<T, unsigned int> || std::is_same_v<T, unsigned long> || std::is_same_v<T, unsigned long long> || std::is_same_v<T, char> || std::is_same_v<T, short> || std::is_same_v<T, int> || std::is_same_v<T, long> || std::is_same_v<T, long long>
void whole_only(T);

using natural_numbers = typename tag::merge_tags_and_types<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>::type;
using whole_numbers   = typename tag::merge_tags_and_types<signed char, short, int, long, long long, natural_numbers>::type;
using real_numbers    = typename tag::merge_tags_and_types<float, double, long double>::type;
using numbers         = typename tag::merge_tags_and_types<whole_numbers, real_numbers>::type;

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