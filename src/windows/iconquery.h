#include <node.h>
#include <iostream>
#include <stdexcept>
#include "icon.h"

namespace exicon
{
class IconQuery
{
  private:
    char *source;
    TCHAR *dest;
    HIMAGELIST *imageList;

  public:
    IconQuery();
    ~IconQuery();
    void check(const v8::FunctionCallbackInfo<v8::Value> &args);
    void release();
    void execute(const v8::FunctionCallbackInfo<v8::Value> &args);
};
char *ToString(v8::Local<v8::Value> value);
}