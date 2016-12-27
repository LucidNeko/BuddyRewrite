#ifndef ENUMCLASSHASH_H
#define ENUMCLASSHASH_H

#include <cstddef>

// Credit: http://stackoverflow.com/a/24847480
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#endif // ENUMCLASSHASH_H
