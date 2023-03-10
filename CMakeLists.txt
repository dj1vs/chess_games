cmake_minimum_required(VERSION 3.5)

project(chess_games VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Charts PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts PrintSupport)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        loginwidget.cpp
        loginwidget.h
        userwidget.cpp
        userwidget.h
        adminwidget.cpp
        adminwidget.h
        sqlworker.cpp
        sqlworker.h
        form/formheader.h
        form/formheader.cpp
        form/formwidget.h
        form/formwidget.cpp
        userwidgets/chessgameslistwidget.cpp
        userwidgets/chessgameslistwidget.h
        userwidgets/chessplayersstatswidget.cpp
        userwidgets/chessplayersstatswidget.h
        userwidgets/openingsstatswidget.cpp
        userwidgets/openingsstatswidget.h
        userwidgets/tournamentsstatswidget.cpp
        userwidgets/tournamentsstatswidget.h
        adminwidgets/chessplayerswidget.cpp
        adminwidgets/chessplayerswidget.h
        adminwidgets/gameswidget.cpp
        adminwidgets/gameswidget.h
        adminwidgets/judgeswidget.cpp
        adminwidgets/judgeswidget.h
        adminwidgets/openingswidget.cpp
        adminwidgets/openingswidget.h
        adminwidgets/placeswidget.cpp
        adminwidgets/placeswidget.h
        adminwidgets/tournamentswidget.cpp
        adminwidgets/tournamentswidget.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(chess_games
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET chess_games APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(chess_games SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(chess_games
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(chess_games PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Charts Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(chess_games PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
install(TARGETS chess_games
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(chess_games)
endif()
