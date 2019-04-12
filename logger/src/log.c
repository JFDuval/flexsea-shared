/*
 * Copyright (c) 2017 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "log.h"

typedef struct {
  void *udata;
  log_LockFn lock;
  FILE *fp;
  TLogLevel MIN_LEVEL;
  int is_embedded; 
} s_logger;

static s_logger logger = {
.is_embedded = 0, // add flag based logic set up serial
.MIN_LEVEL = lwarning, // this should be relatively rare
.lock = 0,
.fp = NULL
};
static void lock(void)   {
  if (logger.lock) {
    logger.lock(logger.udata, 1);
  }
}


static void unlock(void) {
  if (logger.lock) {
    logger.lock(logger.udata, 0);
  }
}


void log_set_udata(void *udata) {
  logger.udata = udata;
}


void log_set_lock(log_LockFn fn) {
  logger.lock = fn;
}


void log_set_fp(FILE *fp) {
  logger.fp = fp;
}


void log_set_level(TLogLevel level) {
  logger.MIN_LEVEL = level;
}


void log_set_embedded(int enable) {
  logger.is_embedded = enable ? 1 : 0;
}


void log_log(TLogLevel level, const char *file, int line, const char *fmt, ...) {
if (level > logger.MIN_LEVEL)
	return;
  /* Acquire lock */
  lock();

  /* Get current time */
  time_t t = time(NULL);
  struct tm *lt = localtime(&t);

  /* Log to stderr */
  if (!logger.fp && logger.is_embedded == 0) {
	char dateTime[80];
	char fileName[90];
	char fullPath[100];
	createFolder(DEBUG_LOG);
    NowTime(dateTime);
	appendPath(DEBUG_LOG,dateTime,fileName);
	appendExtension(fileName,".log",fullPath);
	log_set_fp(fopen(fullPath, "a"));
	// We can also log to stderr, but I've commented it out
	/*
    va_list args;
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';
    fprintf(stderr, "%s %-5s %s:%d: ", buf, level_names[level], file, line);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    fflush(stderr);
	*/
  }
  if (logger.is_embedded == 1) {
	// Mike's debug code goes here, copy the code below and above
	int dummy_var =1;
  }
  /* Log to file */
  if (logger.fp && logger.is_embedded == 0) {
    va_list args;
    char buf[32];
    buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';
    fprintf(logger.fp, "%s %-5s %s:%d: ", buf, level_names[level], file, line);
    va_start(args, fmt);
    vfprintf(logger.fp, fmt, args);
    va_end(args);
    fprintf(logger.fp, "\n");
    fflush(logger.fp);
  }

  /* Release lock */
  unlock();
}

#ifdef __cplusplus
}
#endif