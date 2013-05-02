#include <node.h>
#include <v8.h>
#include <unistd.h>
#include <sys/reboot.h>
#ifndef __MACH__
#include <linux/reboot.h>
#endif

using namespace v8;
using namespace node;

Handle<Value> _rebootImmediately(const Arguments& args) {
#ifdef __MACH__
	fprintf(stderr, "Warning: node-reboot on Darwin (OS X) is not supported\n");
	// reboot(RB_NOSYNC);
#else
	reboot(LINUX_REBOOT_CMD_RESTART);
#endif
	return Undefined();
}
	
Handle<Value> _reboot(const Arguments &args) {
#ifdef __MACH__
	fprintf(stderr, "Warning: node-reboot on Darwin (OS X) is not supported\n");
	// According to manpage, OS X does sync()
	// reboot(RB_AUTOBOOT);
#else
	sync();
	reboot(LINUX_REBOOT_CMD_RESTART);
#endif
	return Undefined();
}

extern "C" void
init (Handle<Object> target) {
	NODE_SET_METHOD(target, "reboot", _reboot);
	NODE_SET_METHOD(target, "rebootImmediately", _rebootImmediately);
}

NODE_MODULE(reboot_bindings, init);
