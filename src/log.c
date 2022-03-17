/* ------------------------------------------------------- */

#include <stdio.h>
#include <core/log.h>

/* ------------------------------------------------------- */

int core_log_init() {

  printf("core_log_init()\n");
  
  return 0;
}

int core_log_shutdown() {

  printf("core_log_shutdown()\n");
  
  return 0;
}

/* ------------------------------------------------------- */

int core_log_verbose(const char* msg) {
  printf("[verbose] %s\n", msg);
  return 0;
}

/* ------------------------------------------------------- */

