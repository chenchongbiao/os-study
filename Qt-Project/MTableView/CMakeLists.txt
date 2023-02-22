cmake_minimum_required(VERSION 3.7)

project(MTableView)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find the library
find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Dtk REQUIRED COMPONENTS Core)           # 寻找Dtk组件Core
find_package(Dtk REQUIRED COMPONENTS Widget)         # 寻找Dtk组件Widget

add_executable(${PROJECT_NAME}
    "main.cpp"
    "private/mtableviewprivate_p.h"
    "mtableview.h"
    "mtableview.cpp"
    resources.qrc
)

target_include_directories(MTableView PUBLIC ${DtkWidget_INCLUDE_DIRS} ${OBJECT_BINARY_DIR})
target_link_libraries(MTableView
    ${DtkWidget_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    Dtk::Core
#    dtkwidget
)
