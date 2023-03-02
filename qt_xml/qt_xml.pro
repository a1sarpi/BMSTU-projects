QT += core gui
CONFIG += C++23

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets widgets xml

TARGET = qt_xml
TEMPLATE = app


SOURCES += main.cpp \
           MainWindow.cpp \
           CustomSplashScreen.cpp \
           DraggableMenuBar.cpp \
           XML_Model.cpp \

RESOURCES += Icons/icons.qrc \
             styles.qrc \
             SplashScreens/screens.qrc \
             Font/font.qrc \

HEADERS += MainWindow.h \
           CustomSplashScreen.h \
           DraggableMenuBar.h \
           XML_Model.h
