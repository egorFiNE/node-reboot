#include <node_api.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/reboot.h>
#ifndef __MACH__
#include <linux/reboot.h>
#endif

napi_value Reboot(napi_env env, napi_callback_info info) {
  sync();

  #ifdef __MACH__
    // macOS does sync() before reboot in this mode as well.
    // We are still calling sync() prior because the trust in
    // Darwin is simply not there and because calling sync()
    // twice in a row is not a problem. Better safe than sorry.
    reboot(RB_AUTOBOOT);
  #else
    reboot(LINUX_REBOOT_CMD_RESTART);
  #endif

  return NULL;
}

napi_value RebootImmediately(napi_env env, napi_callback_info info) {
  #ifdef __MACH__
    reboot(RB_NOSYNC);
  #else
    reboot(LINUX_REBOOT_CMD_RESTART);
  #endif

  return NULL;
}

napi_value Halt(napi_env env, napi_callback_info info) {
  sync();

  #ifdef __MACH__
    reboot(RB_HALT);
  #else
    reboot(LINUX_REBOOT_CMD_POWER_OFF);
  #endif

  return NULL;
}

napi_value HaltImmediately(napi_env env, napi_callback_info info) {
  #ifdef __MACH__
    reboot(RB_HALT);
  #else
    reboot(LINUX_REBOOT_CMD_POWER_OFF);
  #endif

  return NULL;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_value fn;

  napi_create_function(env, NULL, 0, Reboot, NULL, &fn);
  napi_set_named_property(env, exports, "reboot", fn);

  napi_create_function(env, NULL, 0, RebootImmediately, NULL, &fn);
  napi_set_named_property(env, exports, "rebootImmediately", fn);

  napi_create_function(env, NULL, 0, Halt, NULL, &fn);
  napi_set_named_property(env, exports, "halt", fn);

  napi_create_function(env, NULL, 0, HaltImmediately, NULL, &fn);
  napi_set_named_property(env, exports, "haltImmediately", fn);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
