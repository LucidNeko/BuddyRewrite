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
               $$PWD/thirdparty/stb/include \
DEPENDPATH += $$PWD/src \
              $$PWD/thirdparty/glm/include \
              $$PWD/thirdparty/json/include \
              $$PWD/thirdparty/stb/include \

SOURCES += src/glad/glad.c \
           src/main.cpp \
    src/assets/assets.cpp \
    src/assets/component.cpp \
    src/assets/entity.cpp \
    src/assets/scene.cpp \
    src/assets/shaderprogram.cpp \
    src/assets/spritesheet.cpp \
    src/assets/texture.cpp \
    src/assets/loaders/component_loader.cpp \
    src/assets/loaders/entity_loader.cpp \
    src/assets/loaders/scene_loader.cpp \
    src/assets/loaders/shaderprogram_loader.cpp \
    src/assets/loaders/spritesheet_loader.cpp \
    src/assets/loaders/texture_loader.cpp \
    src/components/animation.cpp \
    src/components/collider.cpp \
    src/components/rigidbody.cpp \
    src/components/script.cpp \
    src/components/sprite.cpp \
    src/components/transform.cpp \
    src/subsystems/animationsystem.cpp \
    src/subsystems/physicssystem.cpp \
    src/subsystems/spriterenderer.cpp \
    src/utilities/logging/consolelogger.cpp \
    src/utilities/logging/logger.cpp \
    src/utilities/time/systemclock.cpp \
    src/utilities/time/time.cpp \
    src/gamewindow.cpp \
    src/game.cpp \
    src/entitycollection.cpp \
    src/input.cpp \
    src/jsonutil.cpp \
    src/stb/stb_image_impl.cpp \
    src/uuid.cpp

HEADERS  += src/glad/glad.h \
    src/assets/asset.h \
    src/assets/assets.h \
    src/assets/assettype.h \
    src/assets/component.h \
    src/assets/entity.h \
    src/assets/scene.h \
    src/assets/shaderprogram.h \
    src/assets/spritesheet.h \
    src/assets/texture.h \
    src/components/animation.h \
    src/components/collider.h \
    src/components/rigidbody.h \
    src/components/script.h \
    src/components/sprite.h \
    src/components/transform.h \
    src/subsystems/animationsystem.h \
    src/subsystems/physicssystem.h \
    src/subsystems/spriterenderer.h \
    src/utilities/logging/consolelogger.h \
    src/utilities/logging/logger.h \
    src/utilities/logging/nulllogger.h \
    src/utilities/time/systemclock.h \
    src/utilities/time/time.h \
    src/utilities/time/gametime.h \
    src/services.h \
    src/types.h \
    src/systemopengl.h \
    src/gamewindow.h \
    src/game.h \
    src/property.h \
    src/entitycollection.h \
    src/typemap.h \
    src/logging.h \
    src/input.h \
    src/jsonutil.h \
    src/uuid.h

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

