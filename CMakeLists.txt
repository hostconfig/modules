cmake_minimum_required(VERSION 3.15...3.27 FATAL_ERROR)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0042 NEW)

# Create a namespace for the module
set(VENDOR_NAME "hostconfig" CACHE STRING "Name of module author/vendor." FORCE)

# Name of the project (will be the name of the plugin)
project (addon)

file(GLOB SOURCE_FILES "src/hostconfig/modules/hello.cc")

include_directories("/usr/include/node")

configure_file("include/hostconfig.h"                 "include/hostconfig.h")
configure_file("include/hostconfig/config.h"          "include/hostconfig/config.h")
configure_file("include/hostconfig/version.h"         "include/hostconfig/version.h")
configure_file("include/hostconfig/modules/hello.h"   "include/hostconfig/modules/hello.h")

# Build a shared library named after the project
# Alias it to the vendor namespace
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
add_library(${VENDOR_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Include our configured headers
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Include NodeJs development headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

# Link with NodeJs runtime library
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# Give our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  # Generate node.lib
  execute_process(COMMAND ${CMAKE_AR} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET} ${CMAKE_STATIC_LINKER_FLAGS})
endif()
