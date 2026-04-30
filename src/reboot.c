#include <node_api.h>
#include <stdio.h>
#include <unistd.h>

napi_value Reboot(napi_env env, napi_callback_info info) {
  sync();
  printf("reboot world\n");
  fflush(stdout);
  return NULL;
}

napi_value RebootImmediately(napi_env env, napi_callback_info info) {
  printf("reboot immediately world\n");
  fflush(stdout);
  return NULL;
}

napi_value Halt(napi_env env, napi_callback_info info) {
  sync();
  printf("halt world\n");
  fflush(stdout);
  return NULL;
}

napi_value HaltImmediately(napi_env env, napi_callback_info info) {
  printf("halt immediately world\n");
  fflush(stdout);
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
