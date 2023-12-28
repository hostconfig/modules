cmake_minimum_required (VERSION 3.15...3.27 FATAL_ERROR)
cmake_policy (SET CMP0091 NEW)
cmake_policy (SET CMP0042 NEW)

set (CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_LIST_DIR}/share/cmake/modules"
  "${CMAKE_MODULE_PATH}"
)

# Name of the project (will be the name of the plugin)
project (modules VERSION 0.0.0)

# Set the project 'tweak' version number to the git ref
include(GetSourceInfo)
get_source_info()
set (PROJECT_VERSION_TWEAK "-${git_revision}" CACHE STRING "Fourth version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)

# Create a namespace for the module
set(VENDOR_NAME "hostconfig" CACHE STRING "Name of module author/vendor." FORCE)

# We need to include the NodeJs headers somehow...
include_directories("/usr/include/node")

# Include Node-API headers
include(GetNodeAPIHeaders)

# Include Node-API wrappers
include(GetNodeAPIWrappers)

# Add our headers to a list
set(HEADERS)
list(APPEND HEADERS
  "include/hostconfig.h"
  "include/hostconfig/config.h"
  "include/hostconfig/version.h"
  "include/hostconfig/modules/hello.h"
)

# If building out-of-source...
if (NOT ${PROJECT_SOURCE_DIR} EQUAL ${PROJECT_BINARY_DIR})
  # ...copy our headers to the binary directory.
  foreach(HEADER IN LISTS HEADERS)
    configure_file("${HEADER}" "${HEADER}")
  endforeach()
endif()

file(GLOB SOURCE_FILES "src/hostconfig/modules/hello.cpp")

# Start a list of targets to be built
set(TARGETS)

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
set_target_properties(${PROJECT_NAME}
  PROPERTIES
  PREFIX ""
  SUFFIX ".node"
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Add the target to the list
list(APPEND TARGETS ${PROJECT_NAME})

if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  # Generate node.lib
  execute_process(COMMAND ${CMAKE_AR} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET} ${CMAKE_STATIC_LINKER_FLAGS})
endif()



# Optionally, compile some resources to binary
include("CMakeRC.cmake")

cmrc_add_resource_library(icons
	ALIAS ${VENDOR_NAME}::icons
	NAMESPACE ${VENDOR_NAME}::icons

    favicon.ico
)

set_target_properties (icons
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  POSITION_INDEPENDENT_CODE ON
)

# # Add the target to the list
# list(APPEND TARGETS icons)

target_link_libraries(${PROJECT_NAME} PRIVATE ${VENDOR_NAME}::icons)

# Collect and export targets
set (${PROJECT_NAME}_TARGETS ${TARGETS} CACHE STRING "Targets to be built." FORCE)
export(
  TARGETS ${${PROJECT_NAME}_TARGETS}
  FILE ${PROJECT_BINARY_DIR}/share/${VENDOR_NAME}/${PROJECT_NAME}_targets.cmake
  NAMESPACE ${VENDOR_NAME}::
)

# get access to helper functions for creating config files
include(CMakePackageConfigHelpers)

include("share/cmake/modules/JoinPaths.cmake")
join_paths(libdir_for_pc_file "\${exec_prefix}" "${CMAKE_INSTALL_LIBDIR}")
join_paths(includedir_for_pc_file "\${prefix}" "${CMAKE_INSTALL_INCLUDEDIR}")

# create config file
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/share/cmake/${VENDOR_NAME}/${PROJECT_NAME}Config.cmake.in
    ${PROJECT_BINARY_DIR}/share/cmake/${VENDOR_NAME}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${VENDOR_NAME}/${PROJECT_NAME}
)

# generate the version file for the config file
write_basic_package_version_file(
	${PROJECT_BINARY_DIR}/share/cmake/${VENDOR_NAME}/${PROJECT_NAME}ConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

# Create package config file
configure_file(
  ${PROJECT_SOURCE_DIR}/share/${VENDOR_NAME}/${PROJECT_NAME}.pc.in
  ${PROJECT_BINARY_DIR}/lib/pkgconfig/${VENDOR_NAME}/${PROJECT_NAME}.pc
  @ONLY
)
