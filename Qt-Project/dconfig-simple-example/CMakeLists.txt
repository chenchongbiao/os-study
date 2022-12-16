cmake_minimum_required(VERSION 3.1.0)                # 指定cmake最低版本

project(dconfig-example VERSION 1.0.0 LANGUAGES CXX) # 指定项目名称, 版本, 语言 cxx就是c++

set(CMAKE_CXX_STANDARD 11)                           # 指定c++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)                  # 指定c++标准要求,至少为11以上

set(CMAKE_AUTOMOC ON)                                # 支持qt moc
set(CMAKE_AUTORCC ON)                                # support qt resource file # 支持qt资源文件

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)                # 支持 clangd

if (CMAKE_VERSION VERSION_LESS "3.7.0")              # 如果cmake版本小于3.7.0
    set(CMAKE_INCLUDE_CURRENT_DIR ON)                # 设置包含当前目录
endif()
find_package(Qt5 COMPONENTS Core REQUIRED)           # 寻找Qt5组件Core
find_package(Dtk COMPONENTS Core REQUIRED)           # 寻找Dtk组件Core

add_executable(${PROJECT_NAME}                       # 生成可执行文件
    main.cpp
    data.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE        # 添加需要链接的共享库
    Qt5::Core
    dtkcore
)

dconfig_meta_files(APPID dconfig-example BASE ./data FILES ./data/example.json ./data/a/example.json)
dconfig_meta_files(APPID dconfig-example FILES ./data/example.json ./data/a/example.json)