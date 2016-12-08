#include <QApplication>

#include <iostream>
#include <memory>

#include "types.h"
#include "gamewindow.h"
#include "logging.h"
#include "assets/assets.h"
#include "utilities/logging/consolelogger.h"
#include "utilities/logging/nulllogger.h"
#include "utilities/time/systemclock.h"
#include "services.h"
#include "input.h"

std::string ASSETS_DIRECTORY;

int main(int argc, char *argv[])
{
    std::cout << "START" << std::endl;

    QApplication app(argc, argv);

    Services::set<Input>(new Input);
    Services::set<Logger>(new ConsoleLogger());

    LOG_INFO("argc=%d argv=%s", argc, argv[0]);

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
