/* $Id$
 *  Provides functions to file and directory existence check
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

#ifndef HUSKY_FEXIST_H__
#define HUSKY_FEXIST_H__

#include "compiler.h"
#include "huskyext.h"  /* compiler see directory of this .h file */

HUSKYEXT int _fast fexist(const char *filename);
HUSKYEXT long _fast fsize(const char *filename);
HUSKYEXT time_t _fast fmtime(const char *filename);
HUSKYEXT int _fast direxist(const char *directory);
/*DOC
  Input:  a pointer to a \0 terminated string
  Output: 0 if successfull, 1 else
  FZ:     pathName is a correct directory name
          createDirectoryTree creates the directory and all parental directories
          if they do not exist.

  was taken from hpt\fcommon
*/
HUSKYEXT int  _createDirectoryTree(const char *pathName);

#endif
