/*
 * Copyright (C) 2002 Red Hat, Inc.
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ident "$Id: services.c,v 1.2 2002/11/18 22:08:14 nalin Exp $"

#include <sys/types.h>
#include <netdb.h>

/* Shared settings. */
#define STRUCTURE servent
#define DATABASE  "services"

/* Parser. */
#define ENTNAME   servent
struct servent_data {};

#define libc_hidden_def(ignored)
#define _nss_files_parse_ _nss_directories_parse_

#define TRAILING_LIST_MEMBER            s_aliases
#define TRAILING_LIST_SEPARATOR_P       isspace

#include "files-parse.c"

#define ISSLASH(__c) ((__c) == '/')

LINE_PARSER
("#",
  STRING_FIELD (result->s_name, isspace, 1);
  INT_FIELD (result->s_port, ISSLASH, 10, 0, htons);
  STRING_FIELD (result->s_proto, isspace, 1);
)

/* Lookups. */
#define getnam _nss_directories_getservbyname_r
#define getnam_field s_name
#define getnam_fields s_aliases

#define getnum _nss_directories_getservbyport_r
#define getnum_type int
#define getnum_field s_port

#define setent _nss_directories_setservent
#define getent _nss_directories_getservent_r
#define endent _nss_directories_endservent

#define GET_EXTRA_CRITERIA const char *protocol
#define EXTRA_CRITERIA_NAMES protocol
#define CHECK_EXTRA_CRITERIA(__s) (((__s)->s_proto != NULL) && strcmp((__s)->s_proto, protocol) == 0)

#include "generic.c"
