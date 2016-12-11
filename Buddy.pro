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
    src/entity.cpp \
    src/components/transform.cpp \
    src/components/collider.cpp \
    src/components/component.cpp \
    src/gamewindow.cpp \
    src/game.cpp \
    src/components/rigidbody.cpp \
    src/entitycollection.cpp \
    src/components/sprite.cpp \
    src/utilities/logging/consolelogger.cpp \
    src/utilities/logging/logger.cpp \
    src/subsystems/physicssystem.cpp \
    src/subsystems/spriterenderer.cpp \
    src/utilities/time/systemclock.cpp \
    src/utilities/time/time.cpp \
    src/scenes/scene.cpp \
    src/input.cpp \
    src/components/script.cpp \
    src/assets/assets.cpp \
    src/assets/spritesheet.cpp \
    src/assets/texture.cpp \
    src/assets/loaders/spritesheet_loader.cpp \
    src/assets/loaders/texture_loader.cpp \
    src/jsonutil.cpp \
    src/assets/shaderprogram.cpp \
    src/stb/stb_image_impl.cpp \
    src/assets/loaders/shaderprogram_loader.cpp \
    src/components/animation.cpp \
    src/subsystems/animationsystem.cpp \
    src/assets/loaders/component_loader.cpp \
    src/assets/loaders/entity_loader.cpp \
    src/assets/loaders/scene_loader.cpp \
    src/uuid.cpp

HEADERS  += src/glad/glad.h \
    src/services.h \
    src/types.h \
    src/entity.h \
    src/components/component.h \
    src/components/transform.h \
    src/components/collider.h \
    src/systemopengl.h \
    src/gamewindow.h \
    src/game.h \
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
    src/scenes/scene.h \
    src/assets/assettype.h \
    src/utilities/time/gametime.h \
    src/input.h \
    src/components/script.h \
    src/assets/asset.h \
    src/assets/assets.h \
    src/assets/texture.h \
    src/assets/spritesheet.h \
    src/jsonutil.h \
    src/assets/shaderprogram.h \
    src/components/animation.h \
    src/subsystems/animationsystem.h \
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

