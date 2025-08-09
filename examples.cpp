#include "tagging.hpp"

class my_class
{
public:
    static constexpr std::tag my_tag("my_id");
}

template<typename T>
concept my_concept = (T::my_tag == "my_id");