/* $Id$
 *  Turbo C and Borland C for Windows95/NT compiler-specific declarations
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

/* Borland C/C++ for Win32 */

#ifndef HUSKY_BCW_H
#define HUSKY_BCW_H


#ifndef __TURBOC__
  #error This file may be used only with Turbo C and Borland C !
#endif

#ifndef __WIN32__
  #error This file may be used only with Windows-32bit version of Turbo C or Borland C !
#endif

#  define _stdc cdecl
#  define _intr
#  define _intcast
#  define _veccast
#  define _fast _fastcall
#  define _loadds
#  define near
#  undef  far
#  define far

#  define farread read
#  define farwrite write

#  define _XPENTRY

#  define strcasecmp stricmp
#  define strncasecmp strncmpi

#endif
