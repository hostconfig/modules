#include <napi.h>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(hostconfig::icons);

Napi::String Hello(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  return Napi::String::New(env, "hostconfig/modules is online!");
}

Napi::String Favicon(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  auto fs = cmrc::hostconfig::icons::get_filesystem();
  auto data = fs.open("favicon.ico");
  auto length = std::distance(data.begin(), data.end());
  auto favicon = std::string(data.begin(), data.end());

  const char* char_array = favicon.data();

  return Napi::String::New(env, char_array);
}

Napi::String Index(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

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

  return Napi::String::New(env, html);
}

Napi::String About(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

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

  return Napi::String::New(env, html);
}

Napi::Value Add(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 2)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  double arg0 = info[0].As<Napi::Number>().DoubleValue();
  double arg1 = info[1].As<Napi::Number>().DoubleValue();

  Napi::Number num = Napi::Number::New(env, arg0 + arg1);

  return num;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{

  exports.Set(
    Napi::String::New(env, "hello"),
    Napi::Function::New(env, Hello)
  );

  exports.Set(
    Napi::String::New(env, "favicon"),
    Napi::Function::New(env, Favicon)
  );

  exports.Set(
    Napi::String::New(env, "index"),
    Napi::Function::New(env, Index)
  );

  exports.Set(
    Napi::String::New(env, "about"),
    Napi::Function::New(env, About)
  );

  exports.Set(
    Napi::String::New(env, "add"),
    Napi::Function::New(env, Add)
  );

  return exports;
}

NODE_API_MODULE(modules, Init)
