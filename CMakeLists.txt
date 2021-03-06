project(slope C)
cmake_minimum_required(VERSION 2.8)

set(SLOPE_USE_GTK "FALSE")
set(SLOPE_ENABLE_DEBUG "TRUE")

find_package(PkgConfig REQUIRED)
if(SLOPE_USE_GTK MATCHES "TRUE")
   set(SLOPE_HAVE_GTK 1)
   PKG_CHECK_MODULES(DEPENDENCY "gtk+-3.0")
else()
   set(SLOPE_HAVE_GTK 0)
   PKG_CHECK_MODULES(DEPENDENCY "cairo" "glib-2.0" "gobject-2.0")
endif()

if(SLOPE_ENABLE_DEBUG MATCHES "TRUE")
   set(CMAKE_CC_FLAGS "${CMAKE_CC_FLAGS} -Wall -g}")
   set(SLOPE_BUILD_DEBUG 1)
else()
   set(CMAKE_CC_FLAGS "${CMAKE_CC_FLAGS} -O2}")
endif()
   
include_directories(
   "${DEPENDENCY_INCLUDE_DIRS}"
   "${CMAKE_SOURCE_DIR}/src"
)

subdirs(
   "${CMAKE_SOURCE_DIR}/src"
   "${CMAKE_SOURCE_DIR}/demos"
)
