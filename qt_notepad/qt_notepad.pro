QT += core gui
CONFIG += C++23

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets widgets xml xmlpatterns

TARGET = qt_notepad
TEMPLATE = app

SOURCES +=  main.cpp \
            CustomEnvironment/CustomContext.cpp \
            CustomEnvironment/CustomSplashScreen.cpp \
            CustomEnvironment/DraggableMenuBar.cpp \
            FileTabWidget.cpp \
            MainWindow.cpp \
            SyntaxHighlighter.cpp \
            TextEditor.cpp \

RESOURCES += styles.qrc \
             highlight.qrc \
             Icons/Icons.qrc \
             Font/font.qrc \
             SplashScreens/screens.qrc \

HEADERS += CustomEnvironment/CustomContext.h \
           CustomEnvironment/CustomSplashScreen.h \
           CustomEnvironment/DraggableMenuBar.h \
           FileTabWidget.h \
           MainWindow.h \
           SyntaxHighlighter.h \
           TextEditor.h \
