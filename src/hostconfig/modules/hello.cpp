/*************************************************************************//**
 * @file hello.cc
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @version 0.0.0-alpha
 ****************************************************************************/

#include <iostream>
#include <string>
#include <cmrc/cmrc.hpp>
#include <hostconfig/modules/hello.h>

CMRC_DECLARE(hostconfig::icons);

namespace hostconfig {
namespace modules {

// using v8::FunctionCallbackInfo;
// using v8::Isolate;
// using v8::Local;
// using v8::Object;
// using v8::String;
// using v8::Value;
// using v8::Number;

void Hello(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  v8::Isolate* isolate = args.GetIsolate();

  args.GetReturnValue().Set(v8::String::NewFromUtf8(
    isolate,
    "hostconfig/modules is online!"
    ).ToLocalChecked()
  );
}

void Favicon(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  v8::Isolate* isolate = args.GetIsolate();
  auto type = v8::NewStringType::kNormal;

  auto fs = cmrc::hostconfig::icons::get_filesystem();
  auto data = fs.open("favicon.ico");
  auto length = std::distance(data.begin(), data.end());
  auto favicon = std::string(data.begin(), data.end());

  const char* char_array = favicon.data();

  args.GetReturnValue().Set(v8::String::NewFromUtf8(
    isolate,
    char_array,
    type,
    length
    ).ToLocalChecked()
  );
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "hello", Hello);
  NODE_SET_METHOD(exports, "favicon", Favicon);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace modules
}  // namespace hostconfig
