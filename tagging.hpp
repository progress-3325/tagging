#pragma once

namespace std
{
    template<typename A, typename B>
    struct is_same { static constexpr bool value = false; };

    template<typename T>
    struct is_same<T, T> { static constexpr bool value = true; };

    template<typename A, typename B>
    inline constexpr bool is_same_v = is_same<A, B>::value;

    template<typename T, T v>
    struct integral_constant
    {
        static constexpr T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        constexpr operator T() const noexcept { return v; }
        constexpr T operator()() const noexcept { return v; }
    };

    template<bool _val>
    using bool_constant = integral_constant<bool, _val>;
    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;

    template<bool B, class T, class F>
    struct conditional { using type = T; };

    template<class T, class F>
    struct conditional<false, T, F> { using type = F; };

    template< bool B, class T, class F >
    using conditional_t = typename conditional<B, T, F>::type;
    
// ------------------------------------------------------------------------------------------------------------------------------------------------------------ //

    /// @brief Tag type lists are used as the core object which holds all types of the tag in it's type. 
    /// @brief The ...Ts template parameter is used as an ...Args typename to hold multiple tags in an instance.
    /// @tparam ...Ts 
    template<typename... Ts>
    struct tag_type_list;

    /// @brief The container is used to check if one type is in a tag list using the T(type) and L(list) template parameters.
    /// @tparam T 
    /// @tparam L 
    template<typename T, typename L>
    struct container;

    template<typename T>
    struct container<T, tag_type_list<>> : false_type {};
    template<typename T, typename _head, typename... _tail>
    struct container<T, tag_type_list<_tail..., _head>> : conditional_t<is_same_v<T, _head>, true_type, container<T, tag_type_list<_tail...>>> {};

    /// @brief 
    /// @tparam ... 
    template<typename...>
    struct inherit_list;

    template<>
    struct inherit_list<>
    {
        using type = tag_type_list<>;
    };

    template<typename... Ts>
    struct inherit_list<tag_type_list<Ts...>>
    {
        using type = tag_type_list<Ts...>;
    };

    template<typename... Ts1, typename... Ts2, typename... Rest>
    struct inherit_list<tag_type_list<Ts1...>, tag_type_list<Ts2...>, Rest...>
    {
        using type = typename inherit_list<tag_type_list<Ts1..., Ts2...>, Rest...>::type;
    };

    template<typename T>
    struct is_tag : std::false_type {};

    template<typename... Ts>
    struct is_tag<tag_type_list<Ts...>> : std::true_type {};

    template<typename T>
    struct to_tag {
        using type = tag_type_list<T>;
    };

    template<typename... Ts>
    struct to_tag<tag_type_list<Ts...>> {
        using type = tag_type_list<Ts...>;
    };

    template<typename... Args>
    struct multiple_inheritance
    {
        using type = typename inherit_list<typename to_tag<Args>::type...>::type;
    };
}

#define tag(_tag_name, ...) using _tag_name = typename std::multiple_inheritance<__VA_ARGS__>::type;
template<typename _tag, typename _type>
concept contains = std::container<_type, _tag>::value;