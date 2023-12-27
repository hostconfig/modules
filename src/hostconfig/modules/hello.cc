/*************************************************************************//**
 * @file hello.cc
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @version 0.0.0-alpha
 ****************************************************************************/

#include <hostconfig/modules/hello.h>

namespace hostconfig {
namespace modules {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;

void Method(const v8::FunctionCallbackInfo<v8::Value>& args) {

  v8::Isolate* isolate = args.GetIsolate();

  args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "hostconfig/modules is online!").ToLocalChecked());
}

void Func(const v8::FunctionCallbackInfo<v8::Value>& args) {

  v8::Isolate* isolate = args.GetIsolate();

  args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "This is the 'Func' function.").ToLocalChecked());
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "funcyfunc", Func);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace modules
}  // namespace hostconfig
