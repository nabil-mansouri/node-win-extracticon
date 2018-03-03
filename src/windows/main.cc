#include "iconquery.h"

namespace exicon
{
using v8::Object;
using v8::FunctionCallbackInfo;
using v8::Local;
using v8::Value;
void GetIcon(const FunctionCallbackInfo<Value> &args)
{
    IconQuery query = IconQuery();
    query.execute(args);
}
void init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "getIcon", GetIcon);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

} // namespace demo