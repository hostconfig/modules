/**
 * @file class.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <napi.h>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(hostconfig::icons);

namespace Hostconfig
{

/**
 * @brief
 */
class Modules : public Napi::Addon<Modules>
{
public:

  Modules(Napi::Env env, Napi::Object exports);

private:

  Napi::Value Hello(const Napi::CallbackInfo& info);
  Napi::Value Favicon(const Napi::CallbackInfo& info);
  Napi::Value Index(const Napi::CallbackInfo& info);
  Napi::Value About(const Napi::CallbackInfo& info);
  Napi::Value Add(const Napi::CallbackInfo& args);
  Napi::Value Hex(const Napi::CallbackInfo& args);

};

} // namespace Hostconfig
