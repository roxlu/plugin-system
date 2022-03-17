/* ------------------------------------------------------- */

#include <stdio.h>
#include <core/log.h>
#include <module/encoder.h>

/* ------------------------------------------------------- */

static int encoder_create();
static int encoder_destroy();

/* ------------------------------------------------------- */

/* The module load function which is loaded at run-time. */
int encoder_load() {

  printf("encoder_load()\n");

  core_log_verbose("Logging from `encoder_load()`.");

  return 0;
}

/* ------------------------------------------------------- */

int encoder_create() {
  printf("encoder_create().\n");
  return 0;
}

int encoder_destroy() {
  printf("encoder_destroy().\n");
  return 0;
}

/* ------------------------------------------------------- */
