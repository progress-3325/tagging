#pragma once

namespace std
{
    // with a template, you can create typenames for functions and classes
    // (also constexpr variables).
    // typenames can be any type, you can limit the power of a template
    // with the requires keyword.
    template<typename A, typename B>
    struct is_same { static constexpr bool value = false; };

    // is_same has 2 template parameters (2 typenames), however, in the case
    // that both parameters are the same typename, the value will change.
    template<typename T>
    struct is_same<T, T> { static constexpr bool value = true; };

    // is_same_v is a constexpr boolean type, meaning that it's initialized
    // at compile time, and the template parameters are used for the is_same
    // struct, you can't tell if typenames are the same, however in case
    // they are, the default struct will be overloaded with the 
    // is_same<T, T> struct.
    template<typename A, typename B>
    inline constexpr bool is_same_v = is_same<A, B>::value;

    // template parameters can be a value itself. Think of how you tell an array
    // it's size, that's basically it! Except it does count as completely different
    // type if you have differen't values there.
    template<typename T, T v>
    struct integral_constant
    {
        static constexpr T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        constexpr operator T() const noexcept { return v; }
        constexpr T operator()() const noexcept { return v; }
    };

    // of course, the values can be preset or they can be typenames, as shown
    // in the previous example.
    template<bool _val>
    using bool_constant = integral_constant<bool, _val>;
    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;

    template<bool B, typename T, typename F>
    struct conditional { using type = T; };

    template<typename T, typename F>
    struct conditional<false, T, F> { using type = F; };

    template<bool B, typename T, typename F>
    using conditional_t = typename conditional<B, T, F>::type;
    
// ------------------------------------------------------------------------------------------------------------------------------------------------------------ //

    /// @brief Tag type lists are used as the core object which holds all types of the tag in it's type. 
    /// @brief The ...Ts template parameter is used as an ...Args typename to hold multiple tags in an instance.
    /// @tparam ...Ts 
    template<typename... Ts>
    // a typename... {} is an enumeration of types which can
    //  go on forever.
    struct tag_type_list;

    /// @brief The container is used to check if one type is in a tag list using the T(type) and L(list) template parameters.
    /// @tparam T 
    /// @tparam L 
    template<typename T, typename L>
    struct container;

    template<typename T>
    struct container<T, tag_type_list<>> : false_type {}; // if tag_type_list is empty in this container, it will return a constexpr false type
    template<typename T, typename _head, typename... _tail>
    // this will get computed until they either find a _head to be the same as T, if it isn't it will make a new instance of container
    // and it will check whether or not the head of the next one is equal, and repeat until they find the head or it returns a false_type.
    struct container<T, tag_type_list<_tail..., _head>> : conditional_t<is_same_v<T, _head>, true_type, container<T, tag_type_list<_tail...>>> {}; 

    /// @brief 
    /// @tparam ... 
    template<typename...>
    // the struct can have many typenames,
    // not specifying the name of the type name allows us to create a struct with no template parameters
    struct inherit_list; 

    template<>
    // here is the struct with `no template` template specialization.
    struct inherit_list<> 
    {
        using type = tag_type_list<>; // type itself is a data type
    };

    template<typename... Ts>
    // this specialization allows inherit list to be
    // a tag type list, which will be used for
    // creating tags from existing tags. this is the end
    // result of the next specialization, just one big
    // list of the tag's types.
    struct inherit_list<tag_type_list<Ts...>>
    {
        using type = tag_type_list<Ts...>;
    };

    template<typename... Ts1, typename... Ts2, typename... Rest>
    // this specialization takes all the typenames it get's and
    // recursively merges them into one list. the end result is
    // the previous specialization
    struct inherit_list<tag_type_list<Ts1...>, tag_type_list<Ts2...>, Rest...>
    {
        using type = typename inherit_list<tag_type_list<Ts1..., Ts2...>, Rest...>::type;
    };

    template<typename T>
    // the is_tag struct can be used
    // in constexpr if stamenets and 
    // static assertions
    struct is_tag : std::false_type {};

    template<typename... Ts>
    struct is_tag<tag_type_list<Ts...>> : std::true_type {};

    template<typename T>
    // the to_tag is a struct that creates a
    // tag_type_list out of types, in case it 
    // already is a tag_type list it just keeps
    // it the same as an internal type data type
    struct to_tag 
    {
        using type = tag_type_list<T>;
    };

    template<typename... Ts>
    // this specialization of to_tag let's to_tag work even if it has multiple arguments
    struct to_tag<tag_type_list<Ts...>> 
    {
        using type = tag_type_list<Ts...>;
    };

    template<typename... Args>
    // multiple_inheritance uses the to_tag struct
    // to get tag_type_lists out of variables and
    // tag_type_lists and feeds them to inherit_list
    // through the Ts1..., Ts2..., Rest... specialization
    // if there are also tag_type_lists and variables.
    struct multiple_inheritance
    {
        using type = typename inherit_list<typename to_tag<Args>::type...>::type;
    };
}

#define tag(_tag_name, ...) using _tag_name = typename std::multiple_inheritance<__VA_ARGS__>::type;
template<typename _tag, typename _type>
concept contains = std::container<_type, _tag>::value;