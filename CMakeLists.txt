cmake_minimum_required(VERSION 2.8.3)

project(qore-linenoise-module)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )


FIND_PACKAGE (Qore REQUIRED)

include_directories( ${CMAKE_SOURCE_DIR}/src )
include_directories( ${CMAKE_SOURCE_DIR}/src/linenoise )


set(CPP_SRC
    src/linenoise/linenoise.c
    src/linenoise/utf8.c
)
set(QPP_SRC
    src/linenoise.qpp
)

add_definitions(-DUSE_UTF8)

qore_wrap_qpp(QPP_SOURCES ${QPP_SRC})

SET (module_name "linenoise")

add_library(${module_name} SHARED ${CPP_SRC} ${QPP_SOURCES})

qore_binary_module(${module_name} "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

qore_dist("${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

qore_config_info()


