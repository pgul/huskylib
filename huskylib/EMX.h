/* $Id$
 *
 * HUSKYLIB: common defines, types and functions for HUSKY
 *
 * This is part of The HUSKY Fidonet Software project:
 * see http://husky.sourceforge.net for details
 *
 *
 * HUSKYLIB is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * HUSKYLIB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* EMX for 32-bit OS/2 and RSX for Windows NT (GNU C) */

#ifndef HUSKY_EMX_H
#define HUSKY_EMX_H

#ifndef __LITTLE_ENDIAN__
#  define __LITTLE_ENDIAN__  /* using to select functions/macroses for read & write binary values */
#endif

#  define _stdc
#  define _intr
#  define _intcast
#  define _veccast
#  define _fast
#  define _loadds
#  define cdecl
#  define pascal
#  if defined(__32BIT__)
#    define near
#    undef  far
#    define far
#    define farread(a,b,c)  read(a,b,c)
#    define farwrite(a,b,c) write(a,b,c)
#  endif

#  define mymkdir(a) mkdir((a), 0)
#  define getpid() _getpid()

   int unlock(int handle, long ofs, long length);
   int lock(int handle, long ofs, long length);

#  define strcasecmp stricmp
#  define strncasecmp strnicmp

#  define _XPENTRY

#  define HAS_snprintf  1
#  define HAS_vsnprintf 1
#  define HAS_getpid    1  /* getpid() in process.h */
#  define HAS_spawnvp   1  /* spawnvp() in process.h */
#  define HAS_strftime  1  /* strftime() in time.h  */
#  define HAS_mktime    1  /* mktime() in time.h */
#  define HAS_popen_close  /* popen(); pclose() */

#  define HAS_DIRENT_H  1  /* use "#include <dirent.h>" for opendir() etc. */
#  define HAS_IO_H      1  /* use "#include <io.h>" */
#  define HAS_SHARE_H   1  /* may use "#include <share.h> */
#  define HAS_UNISTD_H  1  /* use "#include <unistd.h> */
#  define HAS_SIGNAL_H  1  /* <signal.h> */
#  define HAS_PROCESS_H   /* may use "#include <process.h> */

#  define USE_STAT_MACROS

typedef unsigned bit;

typedef unsigned char byte;
typedef signed char sbyte;

typedef unsigned short word;
typedef signed short sword;

typedef unsigned long dword;
typedef signed long sdword;

typedef signed short sshort;
typedef unsigned short ushort;

typedef signed long slong;
typedef unsigned long ulong;

#endif