cmake_minimum_required(VERSION 3.1.0)                # 指定cmake最低版本

project(dfilechooseredit-example VERSION 1.0.0 LANGUAGES CXX) # 指定项目名称, 版本, 语言 cxx就是c++

set(CMAKE_CXX_STANDARD 11)                           # 指定c++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)                  # 指定c++标准要求,至少为11以上

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)                # 支持 clangd

if (CMAKE_VERSION VERSION_LESS "3.7.0")              # 如果cmake版本小于3.7.0
    set(CMAKE_INCLUDE_CURRENT_DIR ON)                # 设置包含当前目录
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets)        # 寻找Qt5组件Widgets
find_package(Dtk REQUIRED COMPONENTS Widget)         # 寻找Dtk组件Widget

add_executable(${PROJECT_NAME}                       # 生成可执行文件
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE        # 添加需要链接的共享库
    Qt5::Widgets
    ${DtkWidget_LIBRARIES}
)
