# CMakeLists for duneproc
#
# David Adams
# March 2020
#
# Uses art studio cmake functions but does not use
# studio command line.

cmake_minimum_required(VERSION 3.14.0)
project(duneproc VERSION "00.01.00")

# Load the helpers from studio.
list(APPEND CMAKE_MODULE_PATH $ENV{STUDIO_INC})
include(helpers)

# Copy compiler and linker flags from studio example.
set(CMAKE_CXX_FLAGS "-std=c++17")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-undefined,error")
else()
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
endif()
message("      CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(" CMAKE_CXX_COMPILE_FLAGS: ${CMAKE_CXX_COMPILE_FLAGS}")
message("         CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# Install headers at <PROJECT_NAME> instead of install.
set(CMAKE_INSTALL_INCLUDEDIR "${PROJECT_NAME}")

# Fetch include directories from studio.
find_inc_dirs()
foreach(inc_dir ${inc_dirs_list})
  include_directories(${inc_dir})
endforeach()

find_lib_dirs()
foreach(lib_prod ${lib_prod_list})
  file(GLOB so_list ${map_${lib_prod}}/*.so ${map_${lib_prod}}/*.dylib)
  foreach(so ${so_list})
    string(REGEX REPLACE "^.*/lib([^/]*)\\.(so|dylib)$" "\\1" var ${so})
    set(${var} ${so})
  endforeach()
endforeach()

# root special case!
#file(GLOB root_lib_list $ENV{ROOTSYS}/lib/*.so $ENV{ROOTSYS}/lib/*.dylib)
#foreach(root_so ${root_lib_list})
#  string(REGEX REPLACE "^/.*lib(.*)\\.(so|dylib)$" "\\1" root_var ${root_so})
#  set(root_${root_var} ${root_so})
#endforeach()

# define the set of libraries needed to link a service or module
# library lib lists per plugin
set(service_lib_list)
set(module_lib_list)
set(source_lib_list)
include(libsForPlugins)
libsForPlugins()
set(tool_lib_list "${service_lib_list}")

# Define ROOT variables and functions.
# This is needed to get the command to buid dictionaries.
find_package(ROOT)
include(${ROOT_USE_FILE})

# Subdirectories to process.
#add_subdirectory(Interface)
#add_subdirectory(src)
add_subdirectory(Script)
add_subdirectory(Fcl)
