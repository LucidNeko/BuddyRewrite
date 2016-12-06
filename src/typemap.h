#ifndef TYPEMAP_H
#define TYPEMAP_H

// Inspired from http://gpfault.net/posts/mapping-types-to-values.txt.html

#include <typeindex>
#include <typeinfo>
#include <unordered_map>

template<typename T>
class TypeMap
{
private:
    typedef std::unordered_map<std::type_index, T> Map;

public:
    typedef typename Map::iterator iterator;
    typedef typename Map::const_iterator const_iterator;
    typedef typename Map::value_type value_type;

    const_iterator begin() const { return _map.begin(); }
    const_iterator end() const { return _map.end(); }

    iterator begin() { return _map.begin(); }
    iterator end() { return _map.end(); }

    template<typename Kind>
    const_iterator find() const
    {
        auto key = std::type_index(typeid(Kind));
        return _map.find(key);
    }

    template<typename Kind>
    iterator find()
    {
        auto key = std::type_index(typeid(Kind));
        return _map.find(key);
    }

    template<typename Kind>
    void put(T item)
    {
        auto key = std::type_index(typeid(Kind));
        _map[key] = item;
    }

    template<typename Kind>
    Kind get()
    {
        auto key = std::type_index(typeid(Kind));
        const_iterator it = _map.find(key);
        if(it != _map.end())
        {
            return static_cast<Kind>(_map.find(key)->second);
        }
        return nullptr;
    }

private:
    Map _map;
};

#endif // TYPEMAP_H
