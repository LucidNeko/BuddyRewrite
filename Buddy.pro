#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T22:59:13
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG   += c++11

TARGET = Buddy
TEMPLATE = app

VPATH += src/

INCLUDEPATH += $$PWD/src \
               $$PWD/thirdparty/glm/include \
               $$PWD/thirdparty/json/include \
               $$PWD/thirdparty/stb/include

SOURCES += glad/glad.c \
           main.cpp \
    assets/assets.cpp \
    assets/component.cpp \
    assets/entity.cpp \
    assets/scene.cpp \
    assets/shaderprogram.cpp \
    assets/spritesheet.cpp \
    assets/texture.cpp \
    assets/loaders/component_loader.cpp \
    assets/loaders/entity_loader.cpp \
    assets/loaders/scene_loader.cpp \
    assets/loaders/shaderprogram_loader.cpp \
    assets/loaders/spritesheet_loader.cpp \
    assets/loaders/texture_loader.cpp \
    components/animation.cpp \
    components/collider.cpp \
    components/rigidbody.cpp \
    components/script.cpp \
    components/sprite.cpp \
    components/transform.cpp \
    logging/consolelogger.cpp \
    logging/logger.cpp \
    subsystems/animationsystem.cpp \
    subsystems/physicssystem.cpp \
    subsystems/spriterenderer.cpp \
    gamewindow.cpp \
    game.cpp \
    entitycollection.cpp \
    jsonutil.cpp \
    stb/stb_image_impl.cpp \
    uuid.cpp \
    gametime.cpp \
    src/scripts/testscript.cpp \
    src/subsystems/scriptsystem.cpp \
    src/inputstate.cpp \
    src/subsystems/inputsystem.cpp

HEADERS  += glad/glad.h \
    assets/asset.h \
    assets/assets.h \
    assets/assettype.h \
    assets/component.h \
    assets/entity.h \
    assets/scene.h \
    assets/shaderprogram.h \
    assets/spritesheet.h \
    assets/texture.h \
    components/animation.h \
    components/collider.h \
    components/rigidbody.h \
    components/script.h \
    components/sprite.h \
    components/transform.h \
    logging/consolelogger.h \
    logging/logger.h \
    logging/nulllogger.h \
    subsystems/animationsystem.h \
    subsystems/physicssystem.h \
    subsystems/spriterenderer.h \
    services.h \
    types.h \
    systemopengl.h \
    gamewindow.h \
    game.h \
    property.h \
    entitycollection.h \
    typemap.h \
    logging.h \
    jsonutil.h \
    uuid.h \
    gametime.h \
    src/subsystems/scriptsystem.h \
    src/scripts/testscript.h \
    src/inputstate.h \
    src/subsystems/inputsystem.h

#Copy assets folder to build directory

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
}

CONFIG(release, debug|release) {
    DESTDIR = build/release
}

#Link asset directory to one in the build directory so we can see our assets
windows {
    !exists($$OUT_PWD/$$DESTDIR/assets) {
        !build_pass:message("Will create a link for assets directory")
        QMAKE_POST_LINK += $$quote(mklink /j \"$$DESTDIR/assets\" \"$$PWD/assets\")
    }
}
#TODO: Make work on linux builds

