/**
 * Copyright (c) 2017 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#define DEBUG_LOG "Debug-Log"
#include "../../utilities/inc/folderutilities.h"
#define FILELOG_MAX_LEVEL 7
typedef void (*log_LockFn)(void *udata, int lock);
typedef enum logLevels {lerror, lwarning, linfo, ldebug1, ldebug2, ldebug3, ldebug4} TLogLevel;
static const char *level_names[FILELOG_MAX_LEVEL] = {"ERROR", "WARNING", "INFO", "DEBUG1", "DEBUG2", "DEBUG3","DEBUG4"};

#define LOG(level,...) \
if (level > FILELOG_MAX_LEVEL) ;\
else log_log(level, __FILE__, __LINE__, __VA_ARGS__);

void log_set_udata(void *udata);
void log_set_lock(log_LockFn fn);
void log_set_fp(FILE *fp);
void log_set_level(TLogLevel level);
void log_set_embedded(int enable);

void log_log(TLogLevel level, const char *file, int line, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
