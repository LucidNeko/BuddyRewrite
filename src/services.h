#ifndef SERVICES_H
#define SERVICES_H

//#include <memory>
//#include <typeinfo>
//#include <typeindex>
//#include <unordered_map>

//class Services
//{
//public:
//    Services() = delete;

//    template<typename T>
//    static void set(T* service)
//    {
//        _services[std::type_index(typeid(T))] = std::static_pointer_cast<void>(std::shared_ptr<T>(service));
//    }

//    template<typename T>
////    static std::shared_ptr<T> get()
//    static T* get()
//    {
//        return std::static_pointer_cast<T>(_services[std::type_index(typeid(T))]).get();
//    }

//private:
//    static std::unordered_map<std::type_index, std::shared_ptr<void> > _services;
//};

class Services
{
public:
    Services() = delete;

    template<typename T>
    static void set(T* service)
    {
        _getOrSetService<T>(true, service);
    }

    template<typename T>
    static T* get()
    {
        return _getOrSetService<T>();
    }

private:
    template<typename T>
    static T* _getOrSetService(bool setting = false, T* service = nullptr)
    {
        static T* _service = nullptr;

        if(setting)
        {
            delete _service;
            _service = service;
        }

        return _service;
    }
};

#endif // SERVICES_H
