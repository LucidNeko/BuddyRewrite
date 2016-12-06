#include <QApplication>

#include <iostream>
#include <memory>

#include "types.h"
#include "gamewindow.h"
#include "logging.h"
#include "assets/assets.h"
#include "resources/resource.h"
#include "resources/io/resources.h"
#include "resources/io/filebackedresources.h"
#include "utilities/io/io.h"
#include "utilities/logging/consolelogger.h"
#include "utilities/logging/nulllogger.h"
#include "utilities/time/systemclock.h"
#include "services.h"
#include "input.h"

template<typename T>
class Locator
{
public:
    Locator(std::string name) : _name(name) {}
    ~Locator() = default;

    std::string name() const { return _name; }
    Resource::Type type() const { return Resource::TYPE_NULL; }

private:
    std::string _name;
};

template<>
class Locator<class Texture>
{
public:
    Locator<class Texture>(std::string name) : _name(name) {}
    ~Locator<class Texture>() = default;

    std::string name() const { return _name; }
    Resource::Type type() const { return Resource::TYPE_TEXTURE; }

private:
    std::string _name;
};

int main(int argc, char *argv[])
{
    std::cout << "START" << std::endl;

    QApplication app(argc, argv);

//    QString assetDir = QCoreApplication::applicationDirPath().append("/../../../assets/");

    Services::set<Input>(new Input);
    Services::set<Resources>(new Resources);//new FileBackedResources(assetDir.toStdString()));
    Services::set<Logger>(new ConsoleLogger());

    Services::set<Assets>(new Assets);
    Services::get<Assets>()->setAssetDirectory(IO::assetDirectory());

    LOG_INFO("argc=%d argv=%s", argc, argv[0]);

    Locator<std::string> sl("String Locator");
    Locator<Texture> tl("Texture Locator");
    Locator<U32> ul("U32 Locator");

    LOG_INFO("%s type=%d", sl.name().c_str(), sl.type());
    LOG_INFO("%s type=%d", tl.name().c_str(), tl.type());
    LOG_INFO("%s type=%d", ul.name().c_str(), ul.type());

    Services::set<SystemClock>(new SystemClock());
    Services::set<SystemClock>(nullptr);
    Services::set<SystemClock>(new SystemClock());

    LOG_INFO("Time: %f", Services::get<SystemClock>()->now().seconds());

//    SystemClock c;

//    Time a = c.now();
//    for(int i = 0; i < 10000000; i++) { SystemClock l; }
//    Time b = c.now();

//    Time dt = (b - a);

//    LOG_INFO("%lld, %lld, %lld, %f", a.nanoseconds(), b.nanoseconds(), dt.nanoseconds(), dt.seconds());

    GameWindow w;
    w.show();

    return app.exec();
}
