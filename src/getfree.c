/*
 * This was taken from BinkD and modified a bit for hpt -- ml, 2001
 *
 *
 * $Id$
 */

/*--------------------------------------------------------------------*/
/*       Copyright (c) 1997 by Fydodor Ustinov                        */
/*                             FIDONet 2:5020/79                      */
/*                                                                    */
/*  This program is  free software;  you can  redistribute it and/or  */
/*  modify it  under  the terms of the GNU General Public License as  */
/*  published  by the  Free Software Foundation; either version 2 of  */
/*  the License, or (at your option) any later version. See COPYING.  */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <sys/types.h>


#include <huskylib/compiler.h>
#include <huskylib/huskylib.h>

#ifdef __NT__
#  ifdef __WATCOMC__
#     include <direct.h>
#     ifndef MAXPATHLEN
#       define MAXPATHLEN NAME_MAX
#     endif
#  elif defined (__MSVC__)
#     include <stdlib.h>
#     ifndef MAXPATHLEN
#       define MAXPATHLEN _MAX_PATH
#     endif
#  endif

#  ifndef MAXPATHLEN
#     define MAXPATHLEN 255
#  endif

/*  #include <windows.h> included in typesize.h */

ULONG fc_GetDiskFreeSpace (const char *path)
{
    FARPROC pGetDiskFreeSpaceEx = NULL;
    BOOL rc;
    ULONG freeSpace = ULONG_MAX;


    pGetDiskFreeSpaceEx = GetProcAddress( GetModuleHandle("kernel32.dll"),
        "GetDiskFreeSpaceExA");

    if (pGetDiskFreeSpaceEx)
    {
        ULARGE_INTEGER i64FreeBytesToCaller,i64TotalBytes,i64FreeBytes;
        rc = pGetDiskFreeSpaceEx (path,
            (PULARGE_INTEGER)&i64FreeBytesToCaller,
            (PULARGE_INTEGER)&i64TotalBytes,
            (PULARGE_INTEGER)&i64FreeBytes);
        if (rc != TRUE) {
            w_log (LL_ERR, "GetDiskFreeSpace error: return code = %lu", GetLastError());
            /* return freeSpace;		    Assume enough disk space */
        } else {
            freeSpace = i64FreeBytesToCaller.QuadPart > (ULONGLONG)freeSpace ?
                        freeSpace :
                        (ULONG)i64FreeBytesToCaller.QuadPart;
            /*  Process GetDiskFreeSpaceEx results. */
        }
    }
    else
    {
        DWORD SPC;				/*  sectors per cluster */
        DWORD BPS;				/*  bytes per sector */
        DWORD FC;				/*  number of free clusters */
        DWORD TNC;				/*  total number of clusters */
        char RPN[MAXPATHLEN];	/*  root path */
        char *pRPN;             /*  Pointer to Root path */
        pRPN = RPN;
        if (isalpha(path[0]) && path[1] == ':' ) {
            /*  Drive letter */
            RPN[0] = path[0];
            RPN[1] = ':';
            RPN[2] = '\\';
            RPN[3] = '\0';
        } else if (path[0] == '\\' && path[1] == '\\') {
            /*  UNC path */
            int i;
            RPN[0] = '\\';
            RPN[1] = '\\';
            i = 2;
            /*  copy server name.... */
            do {
                RPN[i] = path[i];
            } while (path[i++] != '\\');
            /*  .... and share name */
            do {
                RPN[i] = path[i];
            } while (path[i++] != '\\');

            RPN[i] = '\0';

        } else {
            /*  Current Drive */
            pRPN = NULL;
        }


        rc = GetDiskFreeSpace (pRPN,&SPC,&BPS,&FC,&TNC);

        if (rc != TRUE) {
            w_log (LL_ERR, "GetDiskFreeSpace error: return code = %lu", GetLastError());
            /* return freeSpace;		    Assume enough disk space */
        } else {
            /* return (unsigned long) (BPS * SPC * FC); */
            if (BPS * SPC >= 1024)
                freeSpace = ((BPS * SPC / 1024l) * FC);
            else
                freeSpace = (FC / (1024 / (BPS * SPC)));
        }
    }
    return freeSpace;
}
#elif defined(__OS2__)

#ifdef __WATCOMC__
#define __IBMC__ 0
#define __IBMCPP__ 0
#endif

#define INCL_DOS
#include <os2.h>


ULONG fc_GetDiskFreeSpace (const char *path)
{
  FSALLOCATE fsa;
  ULONG disknum = 0;
  APIRET rc;

  if (isalpha (path[0]) && path[1] == ':')
    disknum = toupper (path[0]) - 'A' + 1;

  rc = DosQueryFSInfo (disknum, /* Drive number            */
		       FSIL_ALLOC,	    /* Level 1 allocation info */
		       (PVOID) & fsa,	/* Buffer                  */
		       sizeof (fsa));	/* Size of buffer          */

  if (rc)
  {
    w_log (LL_ERR, "DosQueryFSInfo error: return code = %u", rc);
    return ULONG_MAX;		    /* Assume enough disk space */
  }
  else
  {
    /* return fsa.cSectorUnit * fsa.cUnitAvail * fsa.cbSector; */
    if (fsa.cSectorUnit * fsa.cbSector >= 1024)
      return fsa.cUnitAvail * (fsa.cSectorUnit * fsa.cbSector / 1024);
    else
      return fsa.cUnitAvail / (1024 / (fsa.cSectorUnit * fsa.cbSector));
  }
}

#elif defined(__UNIX__)
/*
   This was taken from ifmail, and modified a bit for binkd -- mff, 1997

   Copyright (c) 1993-1995 Eugene G. Crosser

   ifcico is a FidoNet(r) compatible mailer for U*IX platforms.

   You may do virtually what you wish with this software, as long as the
   explicit reference to its original author is retained:

   Eugene G. Crosser <crosser@pccross.msk.su>, 2:5020/230@FidoNet

   THIS SOFTWARE IS PROVIDED AS IS AND COME WITH NO WARRANTY OF ANY KIND,
   EITHER EXPRESSED OR IMPLIED.  IN NO EVENT WILL THE COPYRIGHT HOLDER BE
   LIABLE FOR ANY DAMAGES RESULTING FROM THE USE OF THIS SOFTWARE.
 */


/* TE: test for FreeBSD, NetBSD, OpenBSD or any other BSD 4.4 - derived OS */
#if (defined(__unix__) || defined(unix)) && !defined(USG)
#include <sys/param.h>
#endif
#if defined(BSD)
#if (BSD >= 199103)
  /* now we can be sure we are on BSD 4.4 */
#include <sys/mount.h>
  /* fake the following code to think we had a sys/statfs.h so it uses
     the proper code segments */
#ifndef _SYS_STATFS_H
#define _SYS_STATFS_H
#endif
#endif
#else
  /* we are not on any BSD-like OS */
  /* list other UNIX os'es without getfree mechanism here */
#if defined( __svr4__ ) || defined( __SVR4 ) || defined (__linux__) && defined (__GLIBC__)
#include <sys/statvfs.h>
#ifndef _SYS_STATVFS_H
#define _SYS_STATVFS_H
#elif !defined (__BEOS__)
#include <sys/vfs.h>
#endif /* BEOS */
#endif /* svr4 or linux */

#if defined (__linux__) && !defined(__GLIBC__)
#include <sys/vfs.h>
#ifndef _SYS_STATFS_H
#define _SYS_STATFS_H
#endif /* _SYS_STATFS_H */
#endif /* linux &! GLIBC */

#endif /* not BSD-like OS */

/*
#if !(defined(_SYS_STATFS_H) || defined(_SYS_STATVFS_H))
#error no statfs() or statvfs() in your system!
#endif
*/

#if defined(_SYS_STATFS_H) || defined(_SYS_STATVFS_H)
ULONG fc_GetDiskFreeSpace (const char *path)
{
#ifdef _SYS_STATVFS_H
  struct statvfs sfs;

  if (statvfs (path, &sfs) != 0)
#else
  struct statfs sfs;

  if (statfs (path, &sfs) != 0)
#endif
  {
    w_log (LL_ERR, "cannot statfs \"%s\", assume enough space", path);
    return ULONG_MAX;
  }
  else
  {
    /* return (sfs.f_bsize * sfs.f_bfree); */
    /* return (sfs.f_bsize * sfs.f_bavail); */
    if (sfs.f_bsize >= 1024)
      return ((sfs.f_bsize / 1024l) * sfs.f_bavail);
    else
      return (sfs.f_bavail / (1024l / sfs.f_bsize));
  }
}

#else
ULONG fc_GetDiskFreeSpace (const char *path)
{
  w_log (LL_WARN, "warning: free space doesn't checked in %s",path);
  return ULONG_MAX;
}

#endif

#elif defined(__DOS__)


ULONG fc_GetDiskFreeSpace (const char *path)
{
  w_log (LL_WARN, "warning: free space doesn't checked in %s",path);
  return ULONG_MAX;
}
#else

#error "unknown system!"

#endif
