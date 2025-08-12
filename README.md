# Summary

This repository is a concept about creating a tag system where you can just use a keyword to name a tag and the types you wish to tag. Later you can use the tag for various compile-time type checking, like concept creation.\
This repository has 2 branches:
* Keyword: creates a `tag(_tag_name, ...)` macro and a `contains(_tag, _type)` concept that checks if the mentioned type is included in the mentioned tag
  * tags store their tagged types in a `tag_type_list`,
  * `inherit_list` is used to merge multiple `tag_type_list` instances. For creating tags from tags
  * the `container` struct recursively checks if a `typename` is part of a `tag_type_list`, returning a `std::false_type` if it isn't and a `std::true_type` if it is.
  * the `is_tag` struct is created for extended user use for tag checking.
  * the `to_tag` struct creates a tag_type_lists out of tags and tag_type_lists
  * the `multiple_inheritance` struct creates tag_type_lists using to_tag and uses the final tag_type_list for the inherit_list, making you able to create tags from both existing tags and data types/classes
  * see examples in: [Keyword->examples.cpp](https://github.com/progress-3325/tagging/blob/Keyword/examples.cpp)
* Class: creates a tag class that is used to tag user created classes for concept type checking more meant as a possible STL data type.
  * the `std::tag` class uses a `std::string_view` as its ID type
  * the constructor, overloaded operators, and functions are all `consteval`, meaning that the function must be evaluated at compile-time
  * see examples in: [Class->examples.cpp](https://github.com/progress-3325/tagging/blob/Class/examples.cpp)

---
# Using My Prototype

To use the method I just presented you can use **git bash** to clone the repository and use it like here:\
navigate to your desired folder and use `git clone`
```
git clone https://github.com/progress-3325/tagging
```
in the same directory, use
```
git checkout Keyword
```
or
```
git checkout Class
```
to select which branch of features you want to use

---
now all that's left is to use `#include "pathtofile/tagging.hpp"` and test the features for yourself!
