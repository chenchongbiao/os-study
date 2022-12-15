cmake_minimum_required(VERSION 3.1.0)         # 指定cmake最低版本

project(example1 VERSION 1.0.0 LANGUAGES CXX) # 指定项目名称, 版本, 语言 cxx就是c++

set(CMAKE_CXX_STANDARD 11)                    # 指定c++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)           # 指定c++标准要求,至少为11以上
set(target example1)                          # 指定目标名称

set(CMAKE_AUTOMOC ON)                         # support qt moc # 支持qt moc
set(CMAKE_AUTORCC ON)                         # support qt resource file # 支持qt资源文件
set(CMAKE_AUTOUIC ON)                         # support qt ui file # 支持qt ui文件(非必须)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)         # support clangd # 支持 clangd

if (CMAKE_VERSION VERSION_LESS "3.7.0")       # 如果cmake版本小于3.7.0
    set(CMAKE_INCLUDE_CURRENT_DIR ON)         # 设置包含当前目录
endif()
find_package(Qt5 COMPONENTS Core REQUIRED)    # 寻找Qt5组件Core
find_package(Dtk COMPONENTS Core REQUIRED)    # 寻找Dtk组件Core

add_executable(${target}                      # 生成可执行文件
    main.cpp
    helper.hpp
    ./data.qrc
)

target_link_libraries(${target} PRIVATE       # 添加需要链接的共享库
    Qt5::Core
    dtkcore
)
