/**
 * @file class.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <hostconfig/modules/class.h>

namespace Hostconfig
{

/**
 * @brief Construct a new Hostconfig::Modules object.
 *
 * @param env
 * @param exports
 */
Modules::Modules(Napi::Env env, Napi::Object exports)
{
  DefineAddon(exports, {
    InstanceMethod("hello", &Modules::Hello, napi_enumerable),
    InstanceMethod("favicon", &Modules::Favicon, napi_enumerable),
    InstanceMethod("index", &Modules::Index, napi_enumerable),
    InstanceMethod("about", &Modules::About, napi_enumerable),
    InstanceMethod("add", &Modules::Add, napi_enumerable)
  });
}

/**
 * @brief
 *
 * @param info
 * @return Napi::Value
 */
Napi::Value Modules::Hello(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  return Napi::String::New(env, "hostconfig/modules is online!");
}

/**
 * @brief
 *
 * @param info
 * @return Napi::Value
 */
Napi::Value Modules::Favicon(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  auto fs = cmrc::hostconfig::icons::get_filesystem();
  auto data = fs.open("favicon.ico");
  auto length = std::distance(data.begin(), data.end());
  auto favicon = std::string(data.begin(), data.end());

  return Napi::String::New(env, favicon.data());
}

/**
 * @brief
 *
 * @param info
 * @return Napi::Value
 */
Napi::Value Modules::Index(const Napi::CallbackInfo& info)
{
  const char* html =
  "<!DOCTYPE html>"
  "<html lang=\"en\">"
  "<head>"
  "  <meta charset=\"UTF-8\">"
  "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
  "  <link rel=\"icon\" type=\"image/x-icon\" href=\"favicon.ico\">"
  "  <title>hostconfig/modules</title>"
  "</head>"
  "<body>"
  "  <h1>Success...</h1>"
  "  <p>This is a compiled binary!</p>"
  "</body>"
  "</html>";

  return Napi::String::New(info.Env(), html);
}

/**
 * @brief
 *
 * @param info
 * @return Napi::Value
 */
Napi::Value Modules::About(const Napi::CallbackInfo& info)
{
  const char* html =
  "<!DOCTYPE html>"
  "<html lang=\"en\">"
  "<head>"
  "  <meta charset=\"UTF-8\">"
  "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
  "  <link rel=\"icon\" type=\"image/x-icon\" href=\"favicon.ico\">"
  "  <title>hostconfig/modules</title>"
  "</head>"
  "<body>"
  "  <h1>hostconfig/modules</h1>"
  "  <a href=\"https://github.com/hostconfig/modules\">Read about this project here!</a>"
  "</body>"
  "</html>";

  return Napi::String::New(info.Env(), html);
}

/**
 * @brief
 *
 * @param args
 * @return Napi::Value
 */
Napi::Value Modules::Add(const Napi::CallbackInfo& args)
{
  Napi::Env env = args.Env();

  if (args.Length() < 2)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!args[0].IsNumber() || !args[1].IsNumber())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  double arg0 = args[0].As<Napi::Number>().DoubleValue();
  double arg1 = args[1].As<Napi::Number>().DoubleValue();

  Napi::Number result = Napi::Number::New(env, arg0 + arg1);

  return result;
}

NODE_API_ADDON(Modules)

} // namespace Hostconfig
