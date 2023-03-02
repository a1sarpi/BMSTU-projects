QT += core gui
CONFIG += C++23

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_calculator
TEMPLATE = app


SOURCES += main.cpp \
           Calculator.cpp \
           MainWindow.cpp \
           String_Evaluate.cpp

RESOURCES += media/source.qrc

HEADERS += \
           Calculator.h \
           MainWindow.h \
           Toggle.h \
           String_Evaluate.h





