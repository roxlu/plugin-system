/* ------------------------------------------------------- */

#if defined(__linux)
#  include <dlfcn.h>
#endif

#if defined(_WIN32)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <core/loader.h>

/* ------------------------------------------------------- */

#if defined(__linux)

int core_load_module(const char* lib, void** result) {

  void* handle = NULL;
  
  handle = dlopen(lib, RTLD_NOW | RTLD_GLOBAL);
  if (NULL == handle) {
    printf("Failed to load the module `%s` with error: %s.\n", lib, dlerror());
    return -1;
  }

  *result = handle;

  return 0;
}
  
int core_load_function(void* module, const char* name, void** handle) {

  void* inst = NULL;
  
  inst = (void *)dlsym(module, name);
  if (NULL == inst) {
    printf("Failed to load the function `%s`.\n", name);
    return -1;
  }

  *handle = inst;

  return 0;
}

#endif

#if defined(_WIN32)

int core_load_module(const char* lib, void** result) {

  HMODULE handle = NULL;

  handle = LoadLibrary(lib);
  if (NULL == handle) {
    printf("Failed to load the module `%s with error 0x%08x` %s\n", lib, GetLastError());
    return -1;
  }

  *result = handle;

  return 0;
}
  
int core_load_function(void* module, const char* name, void** handle) {

  void* inst = NULL;
  
  inst = (void *)GetProcAddress(module, name);
  if (NULL == inst) {
    printf("Failed to load the function `%s`.\n", name);
    return -1;
  }

  *handle = inst;

  return 0;
}

#endif


/* ------------------------------------------------------- */
