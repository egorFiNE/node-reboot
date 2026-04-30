#include <node_api.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/reboot.h>
#ifndef __MACH__
#include <linux/reboot.h>
#endif

// Will return false by default
static bool getSingleBooleanArgument(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  bool value = false;

  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  if (argc > 0) {
    napi_valuetype type;
    napi_typeof(env, argv[0], &type);

    if (type != napi_boolean) {
      return false;
    }

    napi_get_value_bool(env, argv[0], &value);
  }

  return value;
}

napi_value Reboot(napi_env env, napi_callback_info info) {
  bool skip_sync = getSingleBooleanArgument(env, info);

  if (!skip_sync) {
    sync();
  }

  #ifdef __MACH__
    // macOS does sync() before reboot in RB_AUTOBOOT mode as well.
    // We are still calling sync() prior because the trust in
    // Darwin is simply not there and because calling sync()
    // twice in a row is not a problem. Better safe than sorry.
    reboot(skip_sync ? RB_NOSYNC : RB_AUTOBOOT);
  #else
    reboot(LINUX_REBOOT_CMD_RESTART);
  #endif

  return NULL;
}

napi_value Halt(napi_env env, napi_callback_info info) {
  bool skip_sync = getSingleBooleanArgument(env, info);

  if (!skip_sync) {
    sync();
  }

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

  napi_create_function(env, NULL, 0, Halt, NULL, &fn);
  napi_set_named_property(env, exports, "halt", fn);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
