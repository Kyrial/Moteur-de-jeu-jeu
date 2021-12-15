QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    billboardobject.cpp \
    cameraobject.cpp \
    controler.cpp \
    gameobject.cpp \
    geometrymeshengine.cpp \
    geometryui.cpp \
    mobileobj.cpp \
    object.cpp \
    transform.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    BasicIO.h \
    billboardobject.h \
    cameraobject.h \
    controler.h \
    gameobject.h \
    geometrymeshengine.h \
    geometryui.h \
    mainwidget.h \
    geometryengine.h \
    mobileobj.h \
    object.h \
    transform.h

RESOURCES += \
    shaders.qrc \
    textures.qrc \
	mesh.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target


