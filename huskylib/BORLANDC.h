/* $Id$
 *  Turbo C and Borland C compiler-specific declarations for any platform
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

/* Borland Turbo C/C++ & Borland C/C++ **************/

#ifndef HUSKY_BORLANDC_H
#define HUSKY_BORLANDC_H

#ifndef __TURBOC__
  #error This file may be used only with Turbo C and Borland C !
#endif

#  define HAS_MALLOC_H 1      /* use "#include <malloc.h>" for malloc() etc. */
#  define HAS_DIR_H    1      /* use "#include <dir.h>" for findfirst() etc. */
#  define HAS_DOS_H    1      /* use "#include <dos.h>" for delay(), intr() etc. */
#  define HAS_IO_H     1      /* access(), open(), ... */
#  define HAS_SHARE_H  1  /* may use "#include <share.h> */
#  define HAS_PROCESS_H   /* may use "#include <process.h> */

#  if __TURBOC__ == 0x0295
#    define HAS_strftime
#    define HAS_mktime
#  endif

#  if defined(__TURBOC__DOS__)     /* Turbo C/C++ & Borland C/C++ for MS-DOS */
#    include "BCD.h"

#  elif defined(__TURBOC__WIN32__) /* Borland C/C++ for Win32 */
#    include "BCW.h"

#  elif defined(__TURBOC__OS2__)   /* Borland C/C++ for OS/2 */
#    include "BCO.h"
#  endif

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
