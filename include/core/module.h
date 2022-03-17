#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#if defined(_WIN32)
#  define RX_EXPORT __declspec(dllexport)
#else
#  define RX_EXPORT
#endif

#endif
