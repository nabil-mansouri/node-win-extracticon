#include "iconquery.h"

using v8::Exception;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

char *exicon::ToString(v8::Local<v8::Value> value)
{
    if (value->IsString())
    {
        String::Utf8Value string(value);
        char *str = (char *)malloc(string.length() + 1);
        strcpy(str, *string);
        return str;
    }
    return NULL;
}

exicon::IconQuery::IconQuery()
{
    this->source = NULL;
    this->dest = NULL;
    this->imageList = NULL;
}
void exicon::IconQuery::check(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    if (!args[0]->IsString() || !args[1]->IsString())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    this->source = ToString(args[0]);
    this->dest = ToString(args[1]);
}

exicon::IconQuery::~IconQuery()
{
    if (this->source != NULL)
    {
        free(this->source);
    }
    if (this->dest != NULL)
    {
        free(this->dest);
    }
    if (this->imageList != NULL)
    {
        this->dest = NULL;
    }
}
void exicon::IconQuery::execute(const FunctionCallbackInfo<Value> &args)
{
    const unsigned argc = 2;
    Isolate *isolate = args.GetIsolate();
    Local<Value> argv[argc]={v8::Undefined(isolate),v8::Undefined(isolate)};
    Local<Function> cb = Local<Function>::Cast(args[2]);
    try
    {
        this->check(args);
        SHFILEINFO sfi = SHFILEINFO();
        SHGetFileInfo(this->source, -1, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX);
        HRESULT hResult = SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void **)&this->imageList);
        if (hResult == S_OK)
        {
            HICON hIcon;
            hResult = ((IImageList *)imageList)->GetIcon(sfi.iIcon, ILD_TRANSPARENT, &hIcon);
            if (hResult == S_OK)
            {
                HRESULT hr = SaveIcon(dest, &hIcon, 1);
                DestroyIcon(hIcon);
            }
            else
            {
                argv[0] = Exception::TypeError(String::NewFromUtf8(isolate, "Failed to read icon"));
                cb->Call(Null(isolate), argc, argv);
                return;
            }
        }
        else
        {
            argv[0] = Exception::TypeError(String::NewFromUtf8(isolate, "Failed to read image list"));
            cb->Call(Null(isolate), argc, argv);
            return;
        }
        //
        argv[1] = Local<Function>::Cast(String::NewFromUtf8(isolate, this->dest));
        cb->Call(Null(isolate), argc, argv);
    }
    catch (std::exception &e)
    {
        argv[0] = Exception::TypeError(String::NewFromUtf8(isolate, e.what()));
        cb->Call(Null(isolate), argc, argv);
    }
}