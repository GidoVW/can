#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

static char msg_t[255];
static bool first_call = true;

void _err_msg(char *filename, int line, int errnum, char *sysc)
{
  fprintf(stderr, "%s:%d: %s: %s\n", filename, line, sysc, strerror(errnum));
}

void _log_msg(char *filename, int line, char *fmt, ...)
{
  va_list vargs;
  fprintf(stderr, "%s:%d: ", filename, line);
  va_start(vargs, fmt);
  vfprintf(stderr, fmt, vargs);
  va_end(vargs);
  fprintf(stderr, "\n"); /* flush */
}

void _log_msg_r(char *filename, int line, char *fmt, ...)
{
  char tmp[255];
  va_list vargs;

  if (first_call) {
    first_call = false;
    strcat(msg_t, filename);
    sprintf(tmp, ":%d: ", line);
    strncat(msg_t, tmp, strlen(tmp));
  }

  va_start(vargs, fmt);
  vsprintf(tmp, fmt, vargs);
  va_end(vargs);
  strncat(msg_t, tmp, strlen(tmp));

  if (strstr(fmt, "\n")) {
    fprintf(stderr, "%s", msg_t);
    first_call = true;
    strncpy(msg_t, "\0", 1);
  }

}
