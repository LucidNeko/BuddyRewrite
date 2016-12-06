#ifndef PROPERTY_H
#define PROPERTY_H

template<typename T>
class Property
{
public:
    Property(const char* name, T value)
        : _name(name),
          _value(value)
    {
    }

    const char* name()
    {
        return _name;
    }

    T get()
    {
        return _value;
    }

    void set(T value)
    {
        _value = value;
    }

private:
    const char* _name;
    T _value;
};

template<typename T>
class ReadOnlyProperty
{
public:
    Property(const char* name, T value)
        : _name(name),
          _value(value)
    {
    }

    const char* name()
    {
        return _name;
    }

    T get()
    {
        return _value;
    }

private:
    const char* _name;
    T _value;
};

#endif // PROPERTY_H
