/*************************************************************************//**
 * @file hostconfig.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @version 0.0.0-alpha
 ****************************************************************************/
#ifndef HOSTCONFIG_H
#define HOSTCONFIG_H

#include "hostconfig/version.h"             // NOLINT(build/include_directory)
#include "hostconfig/config.h"              // NOLINT(build/include_directory)

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

}  // namespace hostconfig

#endif // HOSTCONFIG_H
