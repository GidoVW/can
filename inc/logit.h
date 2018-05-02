#ifndef LOGIT_H
#define LOGIT_H

#include <errno.h>

extern char *logit_version();

#define logit(...)     _log_msg  (__FILE__, __LINE__, __VA_ARGS__)
#define logit_r(...)   _log_msg_r(__FILE__, __LINE__, __VA_ARGS__)
#define syserr(...)    _err_msg  (__FILE__, __LINE__, errno, __VA_ARGS__)

extern void _log_msg  (char *filename, int line, char *fmt, ...);
extern void _log_msg_r(char *filename, int line, char *fmt, ...);
extern void _err_msg  (char *filename, int line, int errnum, char *fmt, ...);

#endif /* LOGIT_H */
