#ifndef CHECKED_CAST_HH
#define CHECKED_CAST_HH

/**
 * Based on checked_cast implementation from the book:
 *    C++ Coding Standard
 *    item 93: Avoid using static_cast on pointers
 */

#include <type_traits>
#include <cassert>

template<typename TO, typename FROM>
static TO checked_cast(FROM* from)
{
    assert(dynamic_cast<TO>(from) == static_cast<TO>(from));
    return static_cast<TO>(from);
}
template<typename TO, typename FROM>
static TO checked_cast(FROM& from)
{
    using TO_PTR = typename std::remove_reference<TO>::type*;
    TO_PTR* suppress_warning = nullptr; (void)suppress_warning;
    assert(dynamic_cast<TO_PTR>(&from) == static_cast<TO_PTR>(&from));
    return static_cast<TO>(from);
}

#endif