#ifndef UUID_H
#define UUID_H

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

    std::string toString() const;

private:
    uuid_union _uuid;
};

#endif // UUID_H
