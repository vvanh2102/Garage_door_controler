QT += core gui serialport
INCLUDEPATH += $$ARDUINO_CORE_PATH
INCLUDEPATH += $$ADAFRUIT_MQTT_PATH

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
SOURCES += \
    comserial.cpp \
    gdc.cpp \
    loginwindow.cpp \
    main.cpp \
    widget.cpp
    $$ARDUINO_CORE_PATH/Arduino.cpp
HEADERS += \
    comserial.h \
    gdc.h \
    loginwindow.h \
    widget.h
    $$ARDUINO_CORE_PATH/Arduino.h
FORMS += \
    loginwindow.ui \
    widget.ui
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    project8.qrc


