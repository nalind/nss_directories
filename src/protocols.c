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

#ident "$Id: protocols.c,v 1.2 2002/11/18 22:08:14 nalin Exp $"

#include <sys/types.h>
#include <netdb.h>

/* Shared information. */
#define STRUCTURE protoent
#define DATABASE  "protocols"

/* Parser. */
#define ENTNAME   protoent
struct protoent_data {};

#define libc_hidden_def(ignored)
#define _nss_files_parse_ _nss_directories_parse_

#define TRAILING_LIST_MEMBER            p_aliases
#define TRAILING_LIST_SEPARATOR_P       isspace

#include "files-parse.c"

LINE_PARSER
("#",
  STRING_FIELD (result->p_name, isspace, 1);
  INT_FIELD (result->p_proto, isspace, 1, 10,);
)

/* Lookups. */
#define getnam _nss_directories_getprotobyname_r
#define getnam_field p_name
#define getnam_fields p_aliases

#define getnum _nss_directories_getprotobynumber_r
#define getnum_type int
#define getnum_field p_proto

#define setent _nss_directories_setprotoent
#define getent _nss_directories_getprotoent_r
#define endent _nss_directories_endprotoent

#include "generic.c"
