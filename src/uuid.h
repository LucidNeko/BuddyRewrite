#ifndef UUID_H
#define UUID_H

#include <functional>
#include <string>

#include "types.h"

class Uuid
{
private:
    struct U128
    {
        U64 first;
        U64 second;
    };

    union uuid_union
    {
        U8 bytes[16];
        U128 number;
    };

public:
    Uuid();
    Uuid(const std::string& string);
    Uuid(const Uuid& source);

    std::string toString() const;

    inline bool operator==(const Uuid& rhs) const
    {
        return _uuid.number.first == rhs._uuid.number.first &&
               _uuid.number.second == rhs._uuid.number.second;
    }

private:
    uuid_union _uuid;
};

namespace std
{
    template<>
    struct hash<Uuid>
    {
        size_t operator()(const Uuid& uuid) const
        {
            return std::hash<std::string>{}(uuid.toString());
        }
    };
}

#endif // UUID_H
