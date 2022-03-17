#ifndef CORE_LOADER_H
#define CORE_LOADER_H

int core_load_module(const char* lib, void** handle);
int core_load_function(void* module, const char* name, void** handle);

#endif
