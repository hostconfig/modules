/*************************************************************************//**
 * @file version.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @version 0.0.0-alpha
 ****************************************************************************/

#ifndef HOSTCONFIG_VERSION_H
#define HOSTCONFIG_VERSION_H

#define HOSTCONFIG_VERSION_MAJOR 0
#define HOSTCONFIG_VERSION_MINOR 0
#define HOSTCONFIG_VERSION_PATCH 0
#define HOSTCONFIG_VERSION_TWEAK 'alpha'

#define HOSTCONFIG_MAKE_VERSION(major, minor, patch)                         \
  ((major) * 0x1000 + (minor) * 0x100 + (patch))


#define HOSTCONFIG_VERSION ( \
    (HOSTCONFIG_VERSION_MAJOR * 10000) +                                     \
    (HOSTCONFIG_VERSION_MINOR * 100)   +                                     \
     HOSTCONFIG_VERSION_PATCH)

#endif // HOSTCONFIG_VERSION_H