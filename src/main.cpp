#include <QApplication>

#include <iostream>
#include <memory>

#include "types.h"
#include "gamewindow.h"
#include "logging.h"
#include "assets/assets.h"
#include "logging/consolelogger.h"
#include "logging/nulllogger.h"
#include "services.h"
#include "gametime.h"

#include "uuid.h"

#include "yaml-cpp/yaml.h"

std::string ASSETS_DIRECTORY;

int main(int argc, char *argv[])
{
    std::cout << "START" << std::endl;

    QApplication app(argc, argv);

    Services::set<Logger>(new ConsoleLogger());

    LOG_INFO("argc=%d argv=%s", argc, argv[0]);

    LOG_INFO("Time: %f", GameTime::now().seconds());

    YAML::Node node = YAML::Load("[1,2,3]");
    LOG_INFO("%d", node.IsSequence());

    Uuid uuid;
    LOG_INFO("UUID1: %s", uuid.toString().c_str());
    Uuid uuid2(uuid.toString());
    LOG_INFO("UUID2: %s", uuid2.toString().c_str());

    for(I32 i = 0; i < 5; i++)
    {
        LOG_INFO("%s", Uuid().toString().c_str());
    }

    GameWindow w;
    w.show();
    return w.exec();
}
