#include <node_api.h>
#include <assert.h>

#include <sys/syscall.h>
#include <linux/fs.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_FNAME_LENGTH 2048
#define UNKNOWN_ERROR 0

void read_string(napi_env env, napi_value value, char *buf, size_t bufsize) {
  napi_valuetype result;
  napi_status status = napi_typeof(env, value, &result);
  assert(status == napi_ok);
  assert(result == napi_string);
  
  size_t ignore;
  status = napi_get_value_string_utf8(env, value, buf, bufsize, &ignore);
  assert(status == napi_ok);
}

napi_value error_code_to_js(napi_env env, int error) {
  napi_value ret;
  napi_status status;
  if(error == 0) status = napi_create_string_utf8(env, "", 0, &ret);
  else if(error == ELOOP) status = napi_create_string_utf8(env, "ELOOP", 5, &ret);
  else if(error == EBUSY) status = napi_create_string_utf8(env, "EBUSY", 5, &ret);
  else if(error == EPERM) status = napi_create_string_utf8(env, "EPERM", 5, &ret);
  else if(error == EROFS) status = napi_create_string_utf8(env, "EROFS", 5, &ret);
  else if(error == EXDEV) status = napi_create_string_utf8(env, "EXDEV", 5, &ret);
  else if(error == EBADF) status = napi_create_string_utf8(env, "EBADF", 5, &ret);
  else if(error == EACCES) status = napi_create_string_utf8(env, "EACCES", 6, &ret);
  else if(error == EDQUOT) status = napi_create_string_utf8(env, "EDQUOT", 6, &ret);
  else if(error == EFAULT) status = napi_create_string_utf8(env, "EFAULT", 6, &ret);
  else if(error == EINVAL) status = napi_create_string_utf8(env, "EINVAL", 6, &ret);
  else if(error == EISDIR) status = napi_create_string_utf8(env, "EISDIR", 6, &ret);
  else if(error == EMLINK) status = napi_create_string_utf8(env, "EMLINK", 6, &ret);
  else if(error == ENOENT) status = napi_create_string_utf8(env, "ENOENT", 6, &ret);
  else if(error == ENOMEM) status = napi_create_string_utf8(env, "ENOMEM", 6, &ret);
  else if(error == ENOSPC) status = napi_create_string_utf8(env, "ENOSPC", 6, &ret);
  else if(error == EEXIST) status = napi_create_string_utf8(env, "EEXIST", 6, &ret);
  else if(error == EACCES) status = napi_create_string_utf8(env, "EACCES", 6, &ret);
  else if(error == EEXIST) status = napi_create_string_utf8(env, "EEXIST", 6, &ret);
  else if(error == EINVAL) status = napi_create_string_utf8(env, "EINVAL", 6, &ret);
  else if(error == EINVAL) status = napi_create_string_utf8(env, "EINVAL", 6, &ret);
  else if(error == ENOENT) status = napi_create_string_utf8(env, "ENOENT", 6, &ret);
  else if(error == ENOTDIR) status = napi_create_string_utf8(env, "ENOTDIR", 7, &ret);
  else if(error == ENOTDIR) status = napi_create_string_utf8(env, "ENOTDIR", 7, &ret);
  else if(error == ENOTEMPTY) status = napi_create_string_utf8(env, "ENOTEMPTY", 9, &ret);
  else if(error == ENAMETOOLONG) status = napi_create_string_utf8(env, "ENAMETOOLONG", 12, &ret);
  else assert(UNKNOWN_ERROR);
  assert(status == napi_ok);
  return ret;
}


napi_value Swap(napi_env env, napi_callback_info info) {
  napi_status status;
  
  
  size_t argc = 4;
  napi_value argv[argc];
  napi_value thisArg;
  void* data;
  status = napi_get_cb_info(env, info, &argc, argv, &thisArg, &data);
  assert(status == napi_ok);
  
  // accept 4 strings
  assert(argc == 4);
  char fnames[argc][MAX_FNAME_LENGTH];
  for(size_t i = 0; i < argc; i++) {
    read_string(env, argv[i], fnames[i], MAX_FNAME_LENGTH);
  }
  
  // now we are ready to do stuff
  errno = 0;
  int src_fd = open(fnames[0], O_DIRECTORY);
  if(errno != 0) return error_code_to_js(env, errno);
  const char* src_path = fnames[1];
  
  errno = 0;
  int dest_fd = open(fnames[2], O_DIRECTORY);
  if(errno != 0) return error_code_to_js(env, errno);
  const char* dest_path = fnames[3];
  
  errno = 0;
  syscall(SYS_renameat2, src_fd, src_path, dest_fd, dest_path, RENAME_EXCHANGE);
  
  return error_code_to_js(env, errno);
}

#define DECLARE_NAPI_METHOD(name, func)                          \
  { name, 0, func, 0, 0, 0, napi_enumerable, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor desc = DECLARE_NAPI_METHOD("swap", Swap);
  status = napi_define_properties(env, exports, 1, &desc);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)

