#pragma once
#include <type_traits>

namespace tag
{
	template<typename... Args>
	struct type_tag_list;

	template<typename check_type, typename type_list>
	struct container {static_assert(std::is_same_v<type_list, type_tag_list>, "second template parameter of a container must be a tag type list!") };

	template<typename check_type>
	struct container<check_type, type_tag_list<>> : std::false_type {};

	template<typename check_type, typename type_list_head, typename... type_list_rest>
	struct container<check_type, type_tag_list<type_list_head, type_list_rest... >> : std::conditional_t<std::is_same_v<check_type, type_list_head>, std::true_type, container<check_type, type_tag_list<type_list_rest...>>> {};

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
		using type = typename inherit_list<type_tag_list<ttl1..., ttl2...>, other_type_lists...>::type;
	};

	template<typename ttl>
	struct is_tag : std::false_type {};

	template<typename... ttl_contents>
	struct is_tag<type_tag_list<ttl_contents...>> : std::true_type {};

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

	template<typename check_type, typename ttl>
	struct push_back_if_absent;

	template<typename check_type, typename... ttl_contents>
	struct push_back_if_absent<check_type, type_tag_list<ttl_contents...>>
	{
		using type = std::conditional_t<container<check_type, type_tag_list<ttl_contents...>>::value, type_tag_list<ttl_contents...>, type_tag_list<ttl_contents..., check_type>>;
	};

	template<typename T>
	struct deduplicate
	{
		using type = type_tag_list<>;
	};

	template<typename ttl_head, typename... ttl_rest>
	struct deduplicate<type_tag_list<ttl_head, ttl_rest...>>
	{
		using deduped_rest = typename deduplicate<type_tag_list<ttl_rest...>>::type;
		using type         = typename push_back_if_absent<ttl_head, deduped_rest>::type;
	};

	template<typename... Args>
	struct merge_tags_and_types
	{
		using merged = typename inherit_list<typename to_tag<Args>::type...>::type;
		using type   = typename deduplicate<merged>::type;
	};

	template<typename ttl, typename check_type>
	concept contains = container<check_type, ttl>::value;
}