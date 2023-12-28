/*************************************************************************//**
 * @file hostconfig.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @version 0.0.0-alpha
 ****************************************************************************/
#ifndef HOSTCONFIG_H
#define HOSTCONFIG_H

// #include <cmrc/cmrc.hpp>

#include <hostconfig/version.h>             // NOLINT(build/include_directory)
#include <hostconfig/config.h>              // NOLINT(build/include_directory)

// CMRC_DECLARE(hostconfig);

// We reserve the hostconfig_* prefix for macros defined in hostconfig public
// API and assume there are no name conflicts with the embedder's code.

/**
 * The hostconfig namespace.
 */
namespace hostconfig {

class Platform;

/**
 * \example process.cc
 */

// namespace icons
// {
// auto fs = cmrc::hostconfig::get_filesystem();
// auto favicon = fs.open("favicon.ico");
// }

}  // namespace hostconfig

#endif // HOSTCONFIG_H
