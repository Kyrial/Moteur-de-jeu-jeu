QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    cameraobject.cpp \
    gameobject.cpp \
    mobileobj.cpp \
    object.cpp \
    transform.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    BasicIO.h \
    cameraobject.h \
    gameobject.h \
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


