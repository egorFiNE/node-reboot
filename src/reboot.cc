#include <node.h>
#include <unistd.h>
#include <sys/reboot.h>
#ifndef __MACH__
#include <linux/reboot.h>
#endif

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void _rebootImmediately(const FunctionCallbackInfo<Value>& args) {
#ifdef __MACH__
	reboot(RB_QUICK);
#else
	reboot(LINUX_REBOOT_CMD_RESTART);
#endif
}

void _reboot(const FunctionCallbackInfo<Value>& args) {
#ifdef __MACH__
	reboot(0);
#else
	sync();
	reboot(LINUX_REBOOT_CMD_RESTART);
#endif
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "reboot", _reboot);
  NODE_SET_METHOD(exports, "rebootImmediately", _rebootImmediately);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}
