include(qge/qge.pri)

#TEMPLATE = vcapp
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gestionnairebattery.cpp \
    gestionnairegrabber.cpp \
    itembattery.cpp \
    lightsource.cpp \
    serial/SerialPort.cpp \
    controller.cpp \
    tty_com.cpp \
    main.cpp

HEADERS += \
    Global.h \
    gestionnairegrabber.h \
    serial/SerialPort.hpp \
    json.hpp \
    lightsource.h \
    gestionnairebattery.h \
    controller.h \
    itembattery.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
