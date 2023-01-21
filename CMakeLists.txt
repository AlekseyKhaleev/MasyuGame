cmake_minimum_required(VERSION 3.2)

project(MasyuGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        resources/resources.qrc
        main.cpp
        GameWidget.cpp   GameWidget.h
        game/MazeModel.cpp game/MazeModel.h
        game/RobotModel.cpp game/RobotModel.h
        game/RobotView.cpp game/RobotView.h
        game/Controller.cpp game/Controller.h
        game/MazeView.cpp game/MazeView.h
        game/LCDView.cpp game/LCDView.h
        game/GameOverView.cpp game/GameOverView.h
        MenuWidget.cpp MenuWidget.h
        MainWidget.cpp MainWidget.h
        ControlsWidget.cpp ControlsWidget.h
        AuthWidget.cpp AuthWidget.h
        AboutWidget.cpp AboutWidget.h
        HighscoresWidget.cpp HighscoresWidget.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MasyuGame
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MasyuGame APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MasyuGame SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MasyuGame
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MasyuGame PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(MasyuGame PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS MasyuGame
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MasyuGame)
endif()
