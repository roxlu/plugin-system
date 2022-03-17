#ifndef CORE_LOADER_H
#define CORE_LOADER_H

#include <core/module.h>

RX_EXPORT int core_load_module(const char* lib, void** handle);
RX_EXPORT int core_load_function(void* module, const char* name, void** handle);

#endif
