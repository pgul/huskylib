/* $Id$ */

#ifndef _AREALIST_H
#define _AREALIST_H

#include "fidoconf/fidoconf.h"

typedef struct arealisttiem {
	int active;
	char *tag;
	char *desc;
} s_arealistitem, *ps_arealistitem;

typedef struct arealist {
	int count;
	int maxcount;
	ps_arealistitem areas;
} s_arealist, *ps_arealist;

FCONF_EXT ps_arealist newAreaList(void);
FCONF_EXT void        freeAreaList(ps_arealist al);
FCONF_EXT int         addAreaListItem(ps_arealist al, int active, char *tag, char *desc);
FCONF_EXT void        sortAreaList(ps_arealist al);
FCONF_EXT char        *formatAreaList(ps_arealist al, int maxlen, char *activechars);

#endif
