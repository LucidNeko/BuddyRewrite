#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <memory>

typedef std::int8_t I8;
typedef std::int16_t I16;
typedef std::int32_t I32;
typedef std::int64_t I64;

typedef std::uint8_t U8;
typedef std::uint16_t U16;
typedef std::uint32_t U32;
typedef std::uint64_t U64;

typedef float  F32;
typedef double F64;

typedef float Radians;
typedef float Degrees;
typedef Radians Angle;

typedef std::weak_ptr<class Scene> SceneWeakHandle;
typedef std::shared_ptr<class Scene> SceneHandle;

typedef std::weak_ptr<class Entity> EntityWeakHandle;
typedef std::shared_ptr<class Entity> EntityHandle;

typedef std::weak_ptr<class Asset> AssetWeakHandle;
typedef std::shared_ptr<class Asset> AssetHandle;

typedef std::weak_ptr<class Resource> ResourceWeakHandle;
typedef std::shared_ptr<class Resource> ResourceHandle;

typedef std::weak_ptr<class Component> ComponentWeakHandle;
typedef std::shared_ptr<class Component> ComponentHandle;

typedef std::weak_ptr<class JsonFile> JsonFileWeakHandle;
typedef std::shared_ptr<class JsonFile> JsonFileHandle;

// NEW ASSET TYPES
typedef std::shared_ptr<class Texture> TextureHandle;
typedef std::shared_ptr<class SpriteSheet> SpriteSheetHandle;

#endif // TYPES_H
