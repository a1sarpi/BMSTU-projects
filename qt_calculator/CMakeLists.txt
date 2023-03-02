cmake_minimum_required(VERSION 3.5)

project(qt_calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        Toggle.h
        Toggle.cpp
        Calculator.h
        Calculator.cpp
        String_Evaluate.h
        String_Evaluate.cpp
        media/source.qrc
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt_calculator
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
else()
    if(ANDROID)
        add_library(qt_calculator SHARED
                ${PROJECT_SOURCES}
                )
    else()
        add_executable(qt_calculator
                ${PROJECT_SOURCES}
                )
    endif()
endif()

target_link_libraries(qt_calculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(qt_calculator PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt_calculator)
endif()