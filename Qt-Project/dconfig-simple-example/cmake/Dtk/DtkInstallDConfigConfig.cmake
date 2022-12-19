# SPDX-FileCopyrightText: 2022 Uniontech Software Technology Co.,Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause

# This cmake file is used to deploy files that dconfig's meta and override configure.
# 这个cmake文件用于部署dconfig的meta数据和覆盖配置的文件。

# cmake_parse_arguments()命令过去是由CMakeParseArguments模块提供的，但它成为了CMake 3.5中的内置命令。
# include(CMakeParseArguments)行在CMake 3.5及以后的版本中不起任何作用，
# 而在CMake的早期版本中，它将定义cmake_parse_arguments()命令。上面的形式确保命令是可用的，无论使用的是什么CMake版本。
include(CMakeParseArguments)

# get subpath according `FILE` and `BASE`.
# e.g: FILE = /a/b/c/d/foo.json, BASE = /a/b, then return SUBPATH = /c/d/
# 根据' FILE '和' BASE '获取子路径。
function(GET_SUBPATH FILE BASE SUBPATH)
    get_filename_component(BASE_FILE_PATH ${BASE} REALPATH)
    get_filename_component(FILE_PATH ${FILE} REALPATH)
    string(REPLACE ${BASE_FILE_PATH} "" SUBPATH_FILE_NAME ${FILE_PATH})
    get_filename_component(SUBPATH_PATH ${SUBPATH_FILE_NAME} DIRECTORY)

    set(${SUBPATH} ${SUBPATH_PATH} PARENT_SCOPE)
endfunction()

include(GNUInstallDirs)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
# CMAKE_INSTALL_PREFIX（后面简称 PREFIX） 是一个非常特殊的变量，
# 在 CMakeLists.txt 中所有的相对路径都会默认把 PREFIX 作为前缀进行拼接，组成绝对路径。
  set(CMAKE_INSTALL_PREFIX /usr)
endif ()

if(NOT DEFINED DSG_DATA_DIR)
    set(DSG_DATA_DIR ${CMAKE_INSTALL_PREFIX}/share/dsg)
endif()

add_definitions(-DDSG_DATA_DIR=${DSG_DATA_DIR})
# deploy some `meta` 's configure.
#
# FILES       - deployed files. 部署文件。
# BASE        - used to get subpath, if it's empty, only copy files, and ignore it's subpath structure.
# APPID       - working for the app.
# COMMONID    - working for common.
#
# e.g:
# dconfig_meta_files(APPID dconfigexample BASE ./configs FILES ./configs/example.json ./configs/a/example.json)
#
function(DCONFIG_META_FILES)
    set(oneValueArgs BASE APPID COMMONID)
    set(multiValueArgs FILES)
    # 使用cmake_parse_arguments可以定义一个带有命名参数的函数或宏。
    cmake_parse_arguments(METAITEM "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    foreach(_current_FILE ${METAITEM_FILES})
        set(SUBPATH "")
        if (DEFINED METAITEM_BASE)
            GET_SUBPATH(${_current_FILE} ${METAITEM_BASE} SUBPATH)
        endif()

        if (DEFINED METAITEM_APPID)
            install(FILES "${_current_FILE}" DESTINATION ${DSG_DATA_DIR}/configs/${METAITEM_APPID}/${SUBPATH})
            message("FILES ${_current_FILE} DESTINATION ${DSG_DATA_DIR}/configs/${METAITEM_APPID}/${SUBPATH}")
        elseif (DEFINED METAITEM_COMMONID)
            install(FILES ${_current_FILE} DESTINATION ${DSG_DATA_DIR}/configs/${SUBPATH})
        else()
            message(FATAL_ERROR "Please set APPID or COMMONID for the meta item." ${_current_FILE})
        endif()
    endforeach()
endfunction()


# deploy some `meta` 's override configure.
#
# configuration for the `meta_name` 's  override configure.
#
# FILES       - deployed files.
# BASE        - used to get subpath, if it's empty, only copy files, and ignore it's subpath structure.
# APPID       - working for the app, if it's empty, working for all app.
# META_NAME   - override for the meta configure.
#
# e.g :
#dconfig_override_files(APPID dconfigexample BASE ./configs META_NAME example  FILES ./configs/dconf-example.override.json ./configs/a/dconf-example.override.a.json)
#
function(DCONFIG_OVERRIDE_FILES)
    set(options)
    set(oneValueArgs BASE APPID META_NAME)
    set(multiValueArgs FILES)

    cmake_parse_arguments(OVERRIDEITEM "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT DEFINED OVERRIDEITEM_META_NAME)
        message(FATAL_ERROR "Please set meta_name for the override configuration." ${FILES})
    endif()

    foreach(_current_FILE ${OVERRIDEITEM_FILES})
        set(SUBPATH "")
        if (DEFINED OVERRIDEITEM_BASE)
            GET_SUBPATH(${_current_FILE} ${OVERRIDEITEM_BASE} SUBPATH)
        endif()

        if (DEFINED OVERRIDEITEM_APPID)
            install(FILES "${_current_FILE}" DESTINATION ${DSG_DATA_DIR}/configs/overrides/${OVERRIDEITEM_APPID}/${OVERRIDEITEM_META_NAME}/${SUBPATH})
        else()
            install(FILES "${_current_FILE}" DESTINATION ${DSG_DATA_DIR}/configs/overrides/${OVERRIDEITEM_META_NAME}/${SUBPATH})
        endif()
    endforeach()
endfunction()
