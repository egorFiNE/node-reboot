#include <node_api.h>
#include <stdio.h>

napi_value Reboot(napi_env env, napi_callback_info info) {
  printf("reboot world\n");
  fflush(stdout);
  return NULL;
}

napi_value Halt(napi_env env, napi_callback_info info) {
  printf("halt world\n");
  fflush(stdout);
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
