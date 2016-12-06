#ifndef ASSETTYPE_H
#define ASSETTYPE_H

#include "types.h"

class AssetType
{
public:
    enum Type
    {
        TYPE_NULL           = 0x00,
        TYPE_TEXTURE        = 0x01,
        TYPE_SHADER_PROGRAM = 0x02,
        TYPE_SPRITE_SHEET   = 0x03,
    };
};

#endif // ASSETTYPE_H
