#pragma once
#include <type_traits>

namespace tag
{
	template<typename... Args>
	struct type_tag_list;

	template<typename check_type, typename type_list>
	struct container;

	template<typename check_type, typename... Ts>
	struct container<check_type, type_tag_list<Ts...>> : std::bool_constant<(std::is_same_v<check_type, Ts> || ...)> {};

	template<typename check_type, typename type_list>
	constexpr bool container_t = container<check_type, type_list>::value;

	template<typename...>
	struct inherit_list;

	template<>
	struct inherit_list<>
	{
		using type = type_tag_list<>;
	};

	template<typename... ttl>
	struct inherit_list<type_tag_list<ttl...>>
	{
		using type = type_tag_list<ttl...>;
	};

	template<typename... ttl1, typename... ttl2, typename... other_type_lists>
	struct inherit_list<type_tag_list<ttl1...>, type_tag_list<ttl2...>, other_type_lists...>
	{
		using type = inherit_list<type_tag_list<ttl1..., ttl2...>, other_type_lists...>::type;
	};

	template<typename... ttl>
	using inherit_list_t = inherit_list<ttl>::type;
	
	template<typename... contents>
	struct to_tag
	{
		using type = type_tag_list<contents...>;
	};

	template<typename... contents>
	struct to_tag<type_tag_list<contents...>>
	{
		using type = type_tag_list<contents...>;
	};

	template<typename... contents>
	using to_tag_t = typename to_tag<type_tag_list<contents...>>::type;

	template<typename check_type, typename ttl>
	struct push_back_if_absent;

	template<typename check_type, typename... ttl_contents>
	struct push_back_if_absent<check_type, type_tag_list<ttl_contents...>>
	{
		using type = std::conditional_t<container<check_type, type_tag_list<ttl_contents...>>::value, type_tag_list<ttl_contents...>, type_tag_list<ttl_contents..., check_type>>;
	};

	template<typename check_type, typename ttl>
	using push_back_if_absent_t = typename push_back_if_absent<check_type, ttl>::type;

	template<typename T>
	struct deduplicate
	{
		using type = type_tag_list<>;
	};

	template<typename ttl_head, typename... ttl_rest>
	struct deduplicate<type_tag_list<ttl_head, ttl_rest...>>
	{
		using deduped_rest = deduplicate_t<type_tag_list<ttl_rest...>>;
		using type         = push_back_if_absent_t<ttl_head, deduped_rest>;
	};

	template<typename T>
	using deduplicate_t = typename deduplicate<T>::type;

	template<typename... Args>
	struct merge_tags_and_types
	{
		using merged = inherit_list_t<to_tag_t<Args>...>;
		using type   = deduplicate_t<merged>;
	};

	template<typename... Args>
	using merge_tags_and_types_t = typename merge_tags_and_types<Args...>::type;

	template<typename ttl, typename check_type>
	concept contains = container_t<check_type, ttl>;
}
