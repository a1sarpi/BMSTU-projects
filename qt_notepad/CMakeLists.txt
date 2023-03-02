cmake_minimum_required(VERSION 3.5)

project(qt_notepad VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Xml REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Xml REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        CustomEnvironment/CustomSplashScreen.h
        CustomEnvironment/CustomSplashScreen.cpp
        CustomEnvironment/CustomContext.h
        CustomEnvironment/CustomContext.cpp
        MainWindow.h
        MainWindow.cpp
        FileTabWidget.h
        FileTabWidget.cpp
        TextEditor.h
        TextEditor.cpp
        SyntaxHighlighter.h
        SyntaxHighlighter.cpp
        highlight_rules.xml
        CustomEnvironment/DraggableMenuBar.cpp
        CustomEnvironment/DraggableMenuBar.h
        Icons/Icons.qrc
        Font/font.qrc
        SplashScreens/screens.qrc
        styles.qrc
        highlight.qrc
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt_notepad
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
else()
    if(ANDROID)
        add_library(qt_notepad SHARED
                ${PROJECT_SOURCES}
                )
    else()
        add_executable(qt_notepad
                ${PROJECT_SOURCES}
                )
    endif()
endif()

target_link_libraries(qt_notepad PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(qt_notepad PRIVATE Qt${QT_VERSION_MAJOR}::Xml)
target_link_libraries(qt_notepad PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(qt_notepad PRIVATE Qt${QT_VERSION_MAJOR}::Gui)

set_target_properties(qt_notepad PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt_notepad)
endif()