/* ------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>
#include <core/log.h>

/* ------------------------------------------------------- */

typedef struct log_context {
  int num;
} log_context;

static log_context* g_log = NULL;
//extern log_context* g_log;

/* ------------------------------------------------------- */

int core_log_init() {

  printf("core_log_init()\n");

  if (NULL == g_log) {
    
    g_log = malloc(sizeof(log_context));
    if (NULL == g_log) {
      printf("Failed to allocate the log context. (exiting).\n");
      exit(EXIT_FAILURE);
    }

    printf("Allocated `g_log` with pointer `%p`.\n", g_log);
  }
  else {
    printf("Already created the `g_log`, with pointer `%p`.\n", g_log);
  }
  
  return 0;
}

int core_log_shutdown() {

  printf("core_log_shutdown()\n");
  
  return 0;
}

/* ------------------------------------------------------- */

int core_log_verbose(const char* msg) {

  core_log_init();
  
  printf("[verbose] %s (g_log: %p)\n", msg, g_log);
  
  return 0;
}

/* ------------------------------------------------------- */

