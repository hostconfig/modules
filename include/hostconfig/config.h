/*************************************************************************//**
 * @file config.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @version 0.0.0-alpha
 *****************************************************************************
*/

#ifndef HOSTCONFIG_CONFIG_H
#define HOSTCONFIG_CONFIG_H

/*************************************************************************//**
 *
 * Tools
 *
 *****************************************************************************
*/

#ifndef __has_attribute
 #define __has_attribute(x) 0
#endif

#ifndef __has_extension
 #define __has_extension __has_feature
#endif

#ifndef __has_feature
 #define __has_feature(x) 0
#endif

#ifndef __has_include
 #define __has_include(x) 0
#endif

#ifndef __has_builtin
 #define __has_builtin(x) 0
#endif

/*************************************************************************//**
 *
 * Platform checks
 *
 *****************************************************************************
*/

#if defined(__MSYS__) || defined(MSYS)
 #define HOSTCONFIG_PLATFORM_IS_MSYS 1
#endif

#if defined(__CYGWIN__) || defined(CYGWIN)
 #define HOSTCONFIG_PLATFORM_IS_CYGWIN 1
#endif

#if defined(__MINGW64__) || defined(__MINGW32__) || defined(MINGW)
 #define HOSTCONFIG_PLATFORM_IS_MINGW 1
#endif

#if defined(_WIN64) || defined(_WIN32) || defined(WIN32)
 #define HOSTCONFIG_PLATFORM_IS_WINDOWS 1
#endif

#if defined(__linux__) || defined(__linux) || defined(linux)
 #define HOSTCONFIG_PLATFORM_IS_LINUX 1
#endif

#if defined(__unix__) || defined(__unix) || defined(unix)
 #define HOSTCONFIG_PLATFORM_IS_UNIX 1
#endif

/*************************************************************************//**
 *
 * Language checks
 *
 *****************************************************************************
*/

#if defined(_MSVC_LANG)
 #define HOSTCONFIG_CPLUSPLUS _MSVC_LANG
#elif defined(__cplusplus)
 #define HOSTCONFIG_CPLUSPLUS __cplusplus
#else
 #undef HOSTCONFIG_CPLUSPLUS
#endif

#if defined(HOSTCONFIG_CPLUSPLUS)
 #define HOSTCONFIG_BEGIN_DECLS extern "C" {
 #define HOSTCONFIG_END_DECLS }
#else
 #define HOSTCONFIG_BEGIN_DECLS
 #define HOSTCONFIG_END_DECLS
#endif

/*************************************************************************//**
 *
 * Create named function macros
 *
 *****************************************************************************
*/

/**
 * @name HOSTCONFIG_STRINGIFY
*/
#ifndef HOSTCONFIG_STRINGIFY
# define HOSTCONFIG_STRINGIFY(n) HOSTCONFIG_STRINGIFY_HELPER(n)
# define HOSTCONFIG_STRINGIFY_HELPER(n) #n
#endif

/**
 * @name DEC
 * @brief Convert integer to decimal digit literals.
*/
#ifndef DEC
 #define DEC(n)                   \
   ('0' + (((n) / 10000000)%10)), \
   ('0' + (((n) / 1000000)%10)),  \
   ('0' + (((n) / 100000)%10)),   \
   ('0' + (((n) / 10000)%10)),    \
   ('0' + (((n) / 1000)%10)),     \
   ('0' + (((n) / 100)%10)),      \
   ('0' + (((n) / 10)%10)),       \
   ('0' +  ((n) % 10))
#endif

/**
 * @name HEX
 * @brief Convert integer to hex digit literals.
*/
#ifndef HEX
 #define HEX(n)              \
    ('0' + ((n)>>28 & 0xf)), \
    ('0' + ((n)>>24 & 0xf)), \
    ('0' + ((n)>>20 & 0xf)), \
    ('0' + ((n)>>16 & 0xf)), \
    ('0' + ((n)>>12 & 0xf)), \
    ('0' + ((n)>>8  & 0xf)), \
    ('0' + ((n)>>4  & 0xf)), \
    ('0' + ((n)     & 0xf))
#endif

#if defined(__has_feature)
 #define HOSTCONFIG_HAS_FEATURE(x) __has_feature(x)
#else
 #define HOSTCONFIG_HAS_FEATURE(x) 0
#endif

#if defined(__has_attribute)
 #define HOSTCONFIG_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
 #define HOSTCONFIG_HAS_ATTRIBUTE(x) 0
#endif

#if defined(__has_c_attribute)
 #define HOSTCONFIG_HAS_C_ATTRIBUTE(x) __has_c_attribute(x)
#else
 #define HOSTCONFIG_HAS_C_ATTRIBUTE(x) 0
#endif

#if defined(__has_cpp_attribute)
 #define HOSTCONFIG_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
 #define HOSTCONFIG_HAS_CPP_ATTRIBUTE(x) 0
#endif

#if defined(__has_include)
 #define HOSTCONFIG_HAS_INCLUDE(x) __has_include(x)
#else
 #define HOSTCONFIG_HAS_INCLUDE(x) 0
#endif

#if defined(__has_builtin)
 #define HOSTCONFIG_HAS_BUILTIN(x) __has_builtin(x)
#else
 #define HOSTCONFIG_HAS_BUILTIN(x) 0
#endif

#if defined(__has_extension)
 #define HOSTCONFIG_HAS_EXTENSION(x) __has_extension(x)
#else
 #define HOSTCONFIG_HAS_EXTENSION(x) 0
#endif

#ifdef _DEBUG
 #define HOSTCONFIG_DEBUG 1
#else
 #define HOSTCONFIG_DEBUG 0
#endif

#define HOSTCONFIG_INTELLISENSE_GUARD __INTELLISENSE__

/*************************************************************************//**
 *
 * Compiler checks
 *
 *****************************************************************************
*/

#if defined(__clang__)
 #define HOSTCONFIG_CLANG_AT_LEAST(major, minor, patch)                      \
  (HOSTCONFIG_MAKE_VERSION(major, minor, patch) <=                           \
   HOSTCONFIG_MAKE_VERSION(                                                  \
   __clang_major__,                                                          \
   __clang_minor__,                                                          \
   __clang_patchlevel__                                                      \
   ))
#else
 #define HOSTCONFIG_CLANG_AT_LEAST(major, minor, patch) (0)
#endif

#if defined(__GNUC__)
 #define HOSTCONFIG_GNUC_AT_LEAST(major, minor, patch)                       \
  (HOSTCONFIG_MAKE_VERSION(major, minor, patch) <=                           \
   HOSTCONFIG_MAKE_VERSION(                                                  \
   __GNUC__,                                                                 \
   __GNUC_MINOR__,                                                           \
   __GNUC_PATCHLEVEL__                                                       \
   ))
#else
 #define HOSTCONFIG_GNUC_AT_LEAST(major, minor, patch) (0)
#endif

/*************************************************************************//**
 *
 * Header checks
 *
 *****************************************************************************
*/

#if HOSTCONFIG_HAS_INCLUDE(<node/node.h>)
 #define HAVE_NODE_H 1
#else
 #define HAVE_NODE_H 0
 #error "Error: Cannot find '<node/node.h>' in the include path..."
#endif

#if HOSTCONFIG_HAS_INCLUDE(<node/node_version.h>)
 #define HAVE_NODE_VERSION_H 1
#else
 #define HAVE_NODE_VERSION_H 0
 #error "Error: Cannot find '<node/node.h>' in the include path..."
#endif

#if HOSTCONFIG_HAS_INCLUDE(<node/node_api.h>)
 #define HAVE_NODE_API_H 1
#else
 #define HAVE_NODE_API_H 0
 #warning "Warning: Cannot find '<node/node_api.h>' in the include path..."
#endif

#if HOSTCONFIG_HAS_INCLUDE(<node/node_api_types.h>)
 #define HAVE_NODE_API_TYPES_H 1
#else
 #define HAVE_NODE_API_TYPES_H 0
 #warning "Warning: Cannot find '<node/node_api_types.h>' in the include path..."
#endif

#if HOSTCONFIG_HAS_INCLUDE(<node/js_native_api.h>)
 #define HAVE_JS_NATIVE_API_H 1
#else
 #define HAVE_JS_NATIVE_API_H 0
 #warning "Warning: Cannot find '<node/js_native_api.h>' in the include path..."
#endif

#if HOSTCONFIG_HAS_INCLUDE(<node/js_native_api_types.h>)
 #define HAVE_JS_NATIVE_API_TYPES_H 1
#else
 #define HAVE_JS_NATIVE_API_TYPES_H 0
 #warning "Warning: Cannot find '<node/js_native_api_types.h>' in the include path..."
#endif

// ...

#if HOSTCONFIG_HAS_INCLUDE(<node/uv.h>)
 #define HAVE_UV_H 1
#else
 #define HAVE_UV_H 0
 #error "Error: Cannot find '<node/uv.h>' in the include path..."
#endif

/**
#include "v8-array-buffer.h"       // NOLINT(build/include_directory)
#include "v8-container.h"          // NOLINT(build/include_directory)
#include "v8-context.h"            // NOLINT(build/include_directory)
#include "v8-data.h"               // NOLINT(build/include_directory)
#include "v8-date.h"               // NOLINT(build/include_directory)
#include "v8-debug.h"              // NOLINT(build/include_directory)
#include "v8-exception.h"          // NOLINT(build/include_directory)
#include "v8-extension.h"          // NOLINT(build/include_directory)
#include "v8-external.h"           // NOLINT(build/include_directory)
#include "v8-function.h"           // NOLINT(build/include_directory)
#include "v8-initialization.h"     // NOLINT(build/include_directory)
#include "v8-internal.h"           // NOLINT(build/include_directory)
#include "v8-isolate.h"            // NOLINT(build/include_directory)
#include "v8-json.h"               // NOLINT(build/include_directory)
#include "v8-local-handle.h"       // NOLINT(build/include_directory)
#include "v8-locker.h"             // NOLINT(build/include_directory)
#include "v8-maybe.h"              // NOLINT(build/include_directory)
#include "v8-memory-span.h"        // NOLINT(build/include_directory)
#include "v8-message.h"            // NOLINT(build/include_directory)
#include "v8-microtask-queue.h"    // NOLINT(build/include_directory)
#include "v8-microtask.h"          // NOLINT(build/include_directory)
#include "v8-object.h"             // NOLINT(build/include_directory)
#include "v8-persistent-handle.h"  // NOLINT(build/include_directory)
#include "v8-primitive-object.h"   // NOLINT(build/include_directory)
#include "v8-primitive.h"          // NOLINT(build/include_directory)
#include "v8-promise.h"            // NOLINT(build/include_directory)
#include "v8-proxy.h"              // NOLINT(build/include_directory)
#include "v8-regexp.h"             // NOLINT(build/include_directory)
#include "v8-script.h"             // NOLINT(build/include_directory)
#include "v8-snapshot.h"           // NOLINT(build/include_directory)
#include "v8-statistics.h"         // NOLINT(build/include_directory)
#include "v8-template.h"           // NOLINT(build/include_directory)
#include "v8-traced-handle.h"      // NOLINT(build/include_directory)
#include "v8-typed-array.h"        // NOLINT(build/include_directory)
#include "v8-unwinder.h"           // NOLINT(build/include_directory)
#include "v8-value-serializer.h"   // NOLINT(build/include_directory)
#include "v8-value.h"              // NOLINT(build/include_directory)
#include "v8-version.h"            // NOLINT(build/include_directory)
#include "v8-wasm.h"               // NOLINT(build/include_directory)
#include "v8config.h"              // NOLINT(build/include_directory)
*/

#if HOSTCONFIG_HAS_INCLUDE(<node/v8.h>)
 #define HAVE_V8_H 1
#else
 #define HAVE_V8_H 0
 #error "Error: Cannot find '<node/v8.h>' in the include path..."
#endif

#if HOSTCONFIG_HAS_INCLUDE(<node/v8config.h>)
 #define HAVE_V8CONFIG_H 1
#else
 #define HAVE_V8CONFIG_H 0
 #error "Error: Cannot find '<node/v8config.h>' in the include path..."
#endif

#if HOSTCONFIG_HAS_INCLUDE(<node/zlib.h>)
 #define HAVE_ZLIB_H 1
#else
 #define HAVE_ZLIB_H 0
 #error "Error: Cannot find '<node/zlib.h>' in the include path..."
#endif

#if HOSTCONFIG_VERSION_MAJOR >= 2
#endif  // HOSTCONFIG_VERSION >= 2

#if HOSTCONFIG_VERSION_MAJOR >= 3
#endif // HOSTCONFIG_VERSION >= 3

#endif // HOSTCONFIG_CONFIG_H
