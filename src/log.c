/******************************************************************************
 * FIDOCONFIG --- library for fidonet configs
 ******************************************************************************
 * log.c : log file maintnance routines
 *
 * Compiled from hpt/log & htick/log 
 * by Stas Degteff <g@grumbler.org>, 2:5080/102@fidonet
 *
 * Portions copyright (C) Matthias Tichy
 *                        Fido:     2:2433/1245 2:2433/1247 2:2432/605.14
 *                        Internet: mtt@tichy.de
 * Portions copyright (C) Max Levenkov
 *                        Fido:     2:5000/117
 *                        Internet: sackett@mail.ru
 * Portions copyright (C) Gabriel Plutzar
 *                        Fido:     2:31/1
 *                        Internet: gabriel@hit.priv.at
 *
 * This file is part of FIDOCONFIG library (part of the Husky FIDOnet
 * software project)
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * FIDOCONFIG library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FIDOCONFIG library; see the file COPYING.  If not, write
 * to the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA
 *
 * See also http://www.gnu.org
 *****************************************************************************
 * $Id$
 */

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <huskylib/huskylib.h>
#include <huskylib/huskylib.h>
//#include "common.h"
#include <huskylib/log.h>

static s_log *husky_log=NULL;

#ifdef __MINGW32__
#ifdef open
#undef open
#endif
#endif

char *logFileDir = NULL;
int logEchoToScreen;
char *logLevels = NULL;
char *screenLogLevels = NULL;


void initLog(char *fc_logFileDir, int fc_logEchoToScreen, char *fc_logLevels, char *fc_screenLogLevels)
{
    logFileDir = fc_logFileDir;
    logEchoToScreen = fc_logEchoToScreen;
    logLevels = fc_logLevels;
    screenLogLevels = fc_screenLogLevels;
    return;
}

s_log *openLog(char *fileName, char *appN)
{
   time_t     currentTime;
   struct tm  *locTime;
   char *pathname=NULL;

   if (!fileName || !fileName[0]) {
      fprintf( stderr, "Logfile not defined, log into screen instead\n" );
      return NULL;
   }

   if( strchr( fileName, '\\' ) || strchr( fileName, '/' ) ) 
     pathname = fileName;
   else
     /* filename without path, construct full pathname  */
     if ( logFileDir && logFileDir[0] ) {
        xstrscat( &pathname, logFileDir, fileName, NULL );
     } else {
        fprintf( stderr, "LogFileDir not defined, log into screen instead\n" );
        return NULL;      
     }
   husky_log = (s_log *) smalloc(sizeof(s_log));
   memset(husky_log, '\0', sizeof(s_log));
   husky_log->logFile = fopen(pathname, "a");
   if (NULL == husky_log->logFile) {
      fprintf(stderr, "Cannot open log '%s': %s\n", fileName,  strerror(errno) );
      nfree(husky_log);
      if( pathname != fileName ) nfree(pathname);
      return NULL;
   } /* endif */

   husky_log->isopen = 1;

   /* copy all informations */
   xstrcat(&husky_log->appName, appN);

   if (logLevels != NULL)
	   xstrcat(&husky_log->keysAllowed, logLevels);
   else
	   xstrcat(&husky_log->keysAllowed, DefaultLogLevels);

   if( logEchoToScreen )
   { if (screenLogLevels != NULL)
	   xstrcat(&husky_log->keysPrinted, screenLogLevels);
     else
	   xstrcat(&husky_log->keysPrinted, DefaultScreenLogLevels);
   } /* else: quiet mode, keysPrinted is empty */

   husky_log->logEcho = logEchoToScreen;

   /* make first line of log */
   currentTime = time(NULL);
   locTime = localtime(&currentTime);
   fprintf(husky_log->logFile, "----------  ");
   fprintf( husky_log->logFile, "%3s %02u %3s %02u, %s\n",
            weekday_ab[locTime->tm_wday], locTime->tm_mday,
            months_ab[locTime->tm_mon], locTime->tm_year%100, husky_log->appName);

   if( pathname != fileName ) nfree(pathname);
   return husky_log;
}

void closeLog()
{
   if (husky_log != NULL) {
      if (husky_log->isopen) {
        fprintf(husky_log->logFile, "\n");
        fclose(husky_log->logFile);
      } /* endif */
      nfree(husky_log->appName);
      nfree(husky_log->keysAllowed);
      nfree(husky_log->keysPrinted);
      nfree(husky_log);
   }
}

void w_log(char key, char *logString, ...)
{
	time_t     currentTime;
	struct tm  *locTime;
	va_list	   ap;
	register char log=0, screen=0;

	if (husky_log) {
		if (husky_log->isopen && strchr(husky_log->keysAllowed, key)) log=1;
		if (husky_log->logEcho && strchr(husky_log->keysPrinted, key)) screen=1;
		if (!husky_log->isopen && key==LL_CRIT) screen=1; /* Critical error to stderr if not logged */
	}else screen=1;

	if (log || screen) {
		currentTime = time(NULL);
		locTime = localtime(&currentTime);

		if (log) {
			fprintf(husky_log->logFile, "%c %02u.%02u.%02u  ",
					key, locTime->tm_hour, locTime->tm_min, locTime->tm_sec);
			va_start(ap, logString);
			vfprintf(husky_log->logFile, logString, ap);
			va_end(ap);
			putc('\n', husky_log->logFile); 
			fflush(husky_log->logFile);
		}

		if (screen) {
			printf("%c %02u.%02u.%02u  ",
					key, locTime->tm_hour, locTime->tm_min, locTime->tm_sec);
			va_start(ap, logString);
			vprintf(logString, ap);
			va_end(ap);
			putchar('\n');
		}
	}
}
