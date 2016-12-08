#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T22:59:13
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG   += c++11

TARGET = Buddy
TEMPLATE = app

INCLUDEPATH += $$PWD/src \
               $$PWD/thirdparty/glm/include \
               $$PWD/thirdparty/json/include/modified
DEPENDPATH += $$PWD/src \
              $$PWD/thirdparty/glm/include \
              $$PWD/thirdparty/json/include/modified

SOURCES += src/glad/glad.c \
           src/main.cpp \
    src/entityfactory.cpp \
    src/entity.cpp \
    src/components/transform.cpp \
    src/components/collider.cpp \
    src/components/component.cpp \
    src/gamewindow.cpp \
    src/game.cpp \
    src/components/componentfactory.cpp \
    src/components/rigidbody.cpp \
    src/entitycollection.cpp \
    src/components/sprite.cpp \
    src/utilities/logging/consolelogger.cpp \
    src/utilities/logging/logger.cpp \
    src/subsystems/physicssystem.cpp \
    src/subsystems/spriterenderer.cpp \
    src/utilities/time/systemclock.cpp \
    src/utilities/time/time.cpp \
    src/scenes/testscene.cpp \
    src/scenes/scene.cpp \
    src/resources/resource.cpp \
    src/utilities/io/io.cpp \
    src/resources/io/filebackedresources.cpp \
    src/resources/io/resources.cpp \
    src/resources/shaderprogram.cpp \
    src/resources/resourcelocator.cpp \
    src/resources/jsonfile.cpp \
    src/input.cpp \
    src/components/script.cpp \
    src/assets/assets.cpp \
    src/assets/spritesheet.cpp \
    src/assets/texture.cpp \
    src/assets/loaders/spritesheet_loader.cpp \
    src/assets/loaders/texture_loader.cpp \
    src/assets/shader.cpp \
    src/assets/loaders/shader_loader.cpp \
    src/jsonutil.cpp

HEADERS  += src/glad/glad.h \
    src/services.h \
    src/types.h \
    src/entity.h \
    src/entityfactory.h \
    src/components/component.h \
    src/components/transform.h \
    src/components/collider.h \
    src/systemopengl.h \
    src/gamewindow.h \
    src/game.h \
    src/components/componentfactory.h \
    src/components/rigidbody.h \
    src/property.h \
    src/entitycollection.h \
    src/components/sprite.h \
    src/components/componentcontainer.h \
    src/typemap.h \
    src/logging.h \
    src/utilities/logging/consolelogger.h \
    src/utilities/logging/logger.h \
    src/utilities/logging/nulllogger.h \
    src/subsystems/physicssystem.h \
    src/subsystems/spriterenderer.h \
    src/utilities/time/systemclock.h \
    src/utilities/time/time.h \
    src/scenes/testscene.h \
    src/scenes/scene.h \
    src/resources/resource.h \
    src/utilities/io/io.h \
    src/resources/io/filebackedresources.h \
    src/resources/io/resources.h \
    src/resources/shaderprogram.h \
    src/resources/resourcelocator.h \
    src/assets/assettype.h \
    src/utilities/time/gametime.h \
    src/resources/jsonfile.h \
    src/input.h \
    src/components/script.h \
    src/assets/asset.h \
    src/assets/assets.h \
    src/assets/texture.h \
    src/assets/spritesheet.h \
    src/assets/shader.h \
    src/jsonutil.h

DISTFILES += \
    assets/fonts/kenpixel_mini_square.ttf \
    assets/audio/a_bannanas_ages.wav \
    assets/audio/coin.wav \
    assets/audio/jump.wav \
    assets/textures/debug.png \
    assets/textures/enemy.png \
    assets/textures/player.png \
    assets/textures/tiles.png \
    assets/shaders/sprite.frag \
    assets/shaders/text.frag \
    assets/shaders/sprite.vert \
    assets/shaders/text.vert \
    assets/textures/player.png.config

