QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Thread.cpp \
    camera.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Thread.h \
    camera.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# import python lib
win32: LIBS += -L$$PWD/../../../Users/DELL/AppData/Local/Programs/Python/Python38/libs/ -lpython38

INCLUDEPATH += $$PWD/../../../Users/DELL/AppData/Local/Programs/Python/Python38/include
DEPENDPATH += $$PWD/../../../Users/DELL/AppData/Local/Programs/Python/Python38/include

# opencv env
INCLUDEPATH += C:\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\include
LIBS +=C:\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\x64\mingw\bin\libopencv_core411.dll \
       C:\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\x64\mingw\bin\libopencv_highgui411.dll \
       C:\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\x64\mingw\bin\libopencv_imgcodecs411.dll \
       C:\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\x64\mingw\bin\libopencv_imgproc411.dll \
       C:\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\x64\mingw\bin\libopencv_features2d411.dll \
       C:\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\x64\mingw\bin\libopencv_calib3d411.dll \
       C:\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\x64\mingw\bin\libopencv_ml411.dll \
       C:\OpenCV-MinGW-Build-OpenCV-4.1.1-x64\x64\mingw\bin\libopencv_videoio411.dll

# use numpy
win32: LIBS += -L$$PWD/../../../Users/DELL/AppData/Local/Programs/Python/Python38/Lib/site-packages/numpy/core/lib/ -lnpymath

INCLUDEPATH += $$PWD/../../../Users/DELL/AppData/Local/Programs/Python/Python38/Lib/site-packages/numpy/core/include
DEPENDPATH += $$PWD/../../../Users/DELL/AppData/Local/Programs/Python/Python38/Lib/site-packages/numpy/core/include

# camear sdk
win32: LIBS += -L$$PWD/'../../../Program Files (x86)/Specim/SDKs/SpecSensor/2017_369/bin/x64/' -lSpecSensor

INCLUDEPATH +=$$quote(C:\Program Files (x86)\Specim\SDKs\SpecSensor\2017_369\include)
DEPENDPATH +=$$quote(C:\Program Files (x86)\Specim\SDKs\SpecSensor\2017_369\include)
