#ifndef LOG_IT_H
#define LOG_IT_H

#include <errno.h>

#define _log(...)   _log_msg(__FILE__, __LINE__, __VA_ARGS__)
#define _log_r(...) _log_msg_r(__FILE__, __LINE__, __VA_ARGS__)
#define _err(sysc_s)  _err_msg(__FILE__, __LINE__, errno, sysc_s)

extern void _log_msg(char *filename, int line, char *fmt, ...);
extern void _log_msg_r(char *filename, int line, char *fmt, ...);
extern void _err_msg(char *filename, int line, int errnum, char *sysc);

#endif /* LOG_IT_H */
