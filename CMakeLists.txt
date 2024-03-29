cmake_minimum_required(VERSION 2.8.12)

project(qore-linenoise-module)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 1)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

FIND_PACKAGE (Qore 0.9 REQUIRED)

include_directories( ${CMAKE_SOURCE_DIR}/src )
include_directories( ${CMAKE_SOURCE_DIR}/src/linenoise )

# Check for C++11.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CPP_SRC
    src/linenoise/linenoise.c
    src/linenoise/utf8.c
)
set(QPP_SRC
    src/linenoise.qpp
)

add_definitions(-DUSE_UTF8)

qore_wrap_qpp_value(QPP_SOURCES ${QPP_SRC})

SET (module_name "linenoise")

add_library(${module_name} MODULE ${CPP_SRC} ${QPP_SOURCES})

if (DEFINED ENV{DOXYGEN_EXECUTABLE})
    set(DOXYGEN_EXECUTABLE $ENV{DOXYGEN_EXECUTABLE})
endif()

qore_external_binary_module(${module_name} "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

qore_dist("${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

qore_config_info()

if (DOXYGEN_FOUND)
  qore_wrap_dox(QORE_DOX_SRC ${QORE_DOX_TMPL_SRC})
  add_custom_target(QORE_MOD_DOX_FILES DEPENDS ${QORE_DOX_SRC})
  add_dependencies(docs-module QORE_MOD_DOX_FILES)
endif()
