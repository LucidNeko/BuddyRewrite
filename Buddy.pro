#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T22:59:13
#
#-------------------------------------------------

QT       += core gui widgets gamepad
CONFIG   += c++11

TARGET = Buddy
TEMPLATE = app

VPATH += src/

INCLUDEPATH += $$PWD/src \
               $$PWD/thirdparty/glm/include \
               $$PWD/thirdparty/json/include \
               $$PWD/thirdparty/stb/include \
               $$PWD/thirdparty/yaml-cpp/include

linux {
    INCLUDEPATH += /usr/include/GL        \
                   /usr/include

    LIBS += -lGL -lGLU -ldl
}

LIBS += -L$$PWD/thirdparty/yaml-cpp/bin -lyaml-cpp

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
    src/subsystems/inputsystem.cpp \
    src/input/keyboard.cpp \
    src/input/mouse.cpp \
    src/input/gamepad.cpp \
    src/input/input.cpp \
    src/input/gamepad_watcher.cpp \
    src/input/keyboard_watcher.cpp \
    src/input/mouse_watcher.cpp

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
    src/subsystems/inputsystem.h \
    src/input/gamepad.h \
    src/input/keyboard.h \
    src/input/mouse.h \
    src/input/input.h \
    src/input/gamepad_watcher.h \
    src/input/keyboard_watcher.h \
    src/input/mouse_watcher.h \
    src/enumclasshash.h

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

linux {
    !exists($$OUT_PWD/$$DESTDIR/assets) {
        !build_pass:message("Will create a link for assets directory")
        QMAKE_POST_LINK += $$quote(ln -s \"$$PWD/assets\" \"$$DESTDIR/assets\")
    }
}
