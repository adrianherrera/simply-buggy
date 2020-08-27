#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int boom() {
  int *p = (int *)0x1;
  *p = 0xDEADBEEF;
  return *p;
}

static int validate_data(uint8_t *buffer, size_t size) {
  if (size < 50) {
    fprintf(stderr, "error: buffer is too small\n");
    return 1;
  }

  if (buffer[10] == 0xab) {
    if (buffer[20] == 0xcd) {
      boom();
    }
  }

  return 0;
}

int main(int argc, char *argv[]) {
  int retcode = 0;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <file>\n", argv[0]);
    return 1;
  }

  FILE *input = fopen(argv[1], "rb");
  if (!input) {
    fprintf(stderr, "error: failed to open `%s`\n", argv[1]);
    return 1;
  }

  if (fseek(input, 0, SEEK_END)) {
    fprintf(stderr, "error: failed to seek to end of `%s`\n", argv[1]);
    retcode = 1;
    goto do_fclose;
  }
  size_t size = ftell(input);
  if (fseek(input, 0, SEEK_SET)) {
    fprintf(stderr, "error: failed to seek to end of `%s`\n", argv[1]);
    retcode = 1;
    goto do_fclose;
  }

  uint8_t *buffer = (uint8_t *)malloc(sizeof(uint8_t) * size);
  if (!buffer) {
    fprintf(stderr, "error: failed to allocate %ld byte buffer\n", size);
    goto do_fclose;
  }

  if (fread(buffer, 1, size, input) != size) {
    fprintf(stderr, "error: failed to read input `%s`\n", argv[1]);
    goto do_free;
  }

  retcode = validate_data(buffer, size);

do_free:
  free(buffer);

do_fclose:
  fclose(input);

  return retcode;
}
