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

/* Watcom C/C++ all variants (DOS-16, DOS-32, Win, OS/2, QNX) */

#ifndef HUSKY_WATCOMC_H
#define HUSKY_WATCOMC_H

#  define mode_t int
#  define HUSKYEXT extern

#  define strcasecmp  stricmp
#  define strncasecmp strnicmp
#  define snprintf    _snprintf
#  define vsnprintf   _vsnprintf
#  define HAS_snprintf
#  define HAS_vsnprintf
#  define HAS_spawnvp
#  define HAS_getpid
#  define HAS_strftime    /* strftime() in time.h  */
#  define HAS_mktime      /* mktime() in time.h */

#  define HAS_MALLOC_H     /* may be used "#include <malloc.h>"  (see alc.h) */
#  define HAS_IO_H         /* may use "#include <io.h> */
#  define HAS_SHARE_H      /* may use "#include <share.h> */
#  define HAS_DIRECT_H
#  define HAS_SYS_UTIME_H  /* #include <sys/utime.h> in alternate to <utime.h> */
#  define HAS_DOS_H
#  define HAS_SIGNAL_H  1  /* <signal.h> */
#  define HAS_PROCESS_H   /* may use "#include <process.h> */

#  define mymkdir(x)    mkdir(x) /*<direct.h>*/
#  define HAS_mkdir
#  include <dos.h>
#  define mysleep(x)    sleep(x) /* dos.h */
#  define HAS_sleep

#  if defined(__WATCOMC__DOS4G__) /* WATCOM C/C++ for DOS4G */
#    include "WCX.h"
#  elif defined(__WATCOMC__DOS__) /* WATCOM C/C++ for MS-DOS (16 bit)*/
#    include "WCD.h"
#  elif defined(__WATCOMC__OS2__)/* WATCOM C/C++ for OS/2 */
#    include "WCO.h"
#  elif defined(__WATCOMC__NT__) /* WATCOM C/C++ for Windows NT */
#    include "WCW.h"
#  endif


typedef unsigned bit;

typedef unsigned char byte;
typedef signed char sbyte;

typedef unsigned short word;
typedef signed short sword;

#ifdef __ALPHA__    /* add other 64 bit systems here */
typedef unsigned int dword;
typedef signed   int sdword;
#else             /* 32 and 16 bit machines */
typedef unsigned long dword;
typedef signed long sdword;
#endif

typedef signed short sshort;
typedef unsigned short ushort;

typedef signed long slong;
typedef unsigned long ulong;

#endif
