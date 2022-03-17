/* ------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <core/log.h>
#include <core/loader.h>
#include <module/encoder.h>

/* ------------------------------------------------------- */

int main(int argc, const char* argv[]) {

  printf("test a\n");
  int r = 0;
  void* encoder = NULL;
  encoder_load_func* load = NULL;

  core_log_init();

#if defined(__linux)

  r = core_load_module("./../lib/libencoder.so", &encoder);
  if (r < 0) {
    printf("Failed to load the encoder lib.\n");
    exit(EXIT_FAILURE);
  }

  r = core_load_function(encoder, "encoder_load", &load);
  if (r < 0) {
    printf("Failed to load the encoder load function.\n");
    exit(EXIT_FAILURE);
  }

  /* Now, trigger the call from the loaded module. */
  load();
  
#endif

  
  
  core_log_shutdown();

  return EXIT_SUCCESS;
}

/* ------------------------------------------------------- */
