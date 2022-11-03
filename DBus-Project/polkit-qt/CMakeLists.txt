cmake_minimum_required(VERSION 3.0.0)

project(polkit-qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5DBus)
find_package(PolkitQt5-1)

set(SOURCES_DAEMON_FILES
    service/main.cpp
    )
add_executable(polkit-qt-daemon ${SOURCES_DAEMON_FILES})

target_link_libraries(polkit-qt-daemon Qt5::Widgets Qt5::DBus PolkitQt5-1::Agent)
