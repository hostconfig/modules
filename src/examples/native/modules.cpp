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

void Index(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  v8::Isolate* isolate = args.GetIsolate();

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

  args.GetReturnValue().Set(v8::String::NewFromUtf8(
    isolate,
    html
    ).ToLocalChecked()
  );
}

void About(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  v8::Isolate* isolate = args.GetIsolate();

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

  args.GetReturnValue().Set(v8::String::NewFromUtf8(
    isolate,
    html
    ).ToLocalChecked()
  );
}

// This is the implementation of the "add" method
// Input arguments are passed using the
// const FunctionCallbackInfo<Value>& args struct
void Add(const v8::FunctionCallbackInfo<v8::Value>& args) {

  v8::Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.
  if (args.Length() < 2) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(v8::Exception::TypeError(
      v8::String::NewFromUtf8(
        isolate,
        "Wrong number of arguments"
      ).ToLocalChecked()
    ));
    return;
  }

  // Check the argument types
  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(v8::Exception::TypeError(
      v8::String::NewFromUtf8(
        isolate,
        "Wrong arguments"
      ).ToLocalChecked()
    ));
    return;
  }

  double a = args[0].As<v8::Number>()->Value();
  double b = args[1].As<v8::Number>()->Value();

  // Perform the operation
  double value = a + b;

  // Store the result
  v8::Local<v8::Number> result = v8::Number::New(isolate, value);

  // Set the return value (using the passed in
  // FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(result);
}

void RunCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {

  v8::Isolate* isolate = args.GetIsolate();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(args[0]);

  const unsigned argc = 1;

  v8::Local<v8::Value> argv[argc] = {
      v8::String::NewFromUtf8(isolate,
                          "hello world").ToLocalChecked() };
  cb->Call(context, Null(isolate), argc, argv).ToLocalChecked();
}

void CreateObject(const v8::FunctionCallbackInfo<v8::Value>& args) {

  v8::Isolate* isolate = args.GetIsolate();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  // Create a new object from the args...
  v8::Local<v8::Object> obj = v8::Object::New(isolate);

  obj->Set(
    context,
    v8::String::NewFromUtf8(isolate, "msg").ToLocalChecked(),
    args[0]->ToString(context).ToLocalChecked()
  ).FromJust();

  args.GetReturnValue().Set(obj);
}

void CreateFunction(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, Add);
  v8::Local<v8::Function> fn = tpl->GetFunction(context).ToLocalChecked();

  // omit this to make it anonymous
  fn->SetName(v8::String::NewFromUtf8(
      isolate, "AddFactory").ToLocalChecked());

  args.GetReturnValue().Set(fn);
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "hello", Hello);
  NODE_SET_METHOD(exports, "favicon", Favicon);
  NODE_SET_METHOD(exports, "index", Index);
  NODE_SET_METHOD(exports, "about", About);
  NODE_SET_METHOD(exports, "add", Add);
}

void InitializeRunCallback(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  NODE_SET_METHOD(module, "exports", RunCallback);
}

void InitializeCreateObject(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  NODE_SET_METHOD(module, "exports", CreateObject);
}

void InitializeCreatFuncion(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  NODE_SET_METHOD(module, "exports", CreateFunction);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace modules
}  // namespace hostconfig

// <!DOCTYPE html>
// <html lang="en">
// <head>
//   <meta charset="UTF-8">
//   <meta name="viewport" content="width=device-width, initial-scale=1.0">
//   <title>Document</title>
// </head>
// <body>

// </body>
// </html>
