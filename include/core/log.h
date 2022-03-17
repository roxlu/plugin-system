#ifndef CORE_LOG_H
#define CORE_LOG_H

#include <core/module.h>

RX_EXPORT int core_log_init();
RX_EXPORT int core_log_verbose(const char* msg);
RX_EXPORT int core_log_shutdown();

#endif
