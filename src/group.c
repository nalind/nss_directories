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

#ident "$Id: group.c,v 1.3 2002/11/19 00:05:07 nalin Exp $"

#include <sys/types.h>
#include <grp.h>
#include "parsers.h"

/* Shared information. */
#define STRUCTURE group
#define DATABASE  "group"

/* Parser. */
#define ENTNAME   grent
#define ENTDATA   grent_data
struct grent_data {};

#define libc_hidden_def(ignored)
#define _nss_files_parse_ _nss_directories_parse_

#define EXTERN_PARSER

#include "files-parse.c"

/* Lookup. */
#define getnam _nss_directories_getgrnam_r
#define getnam_field gr_name

#define getnum _nss_directories_getgrgid_r
#define getnum_type gid_t
#define getnum_field gr_gid

#define setent _nss_directories_setgrent
#define getent _nss_directories_getgrent_r
#define endent _nss_directories_endgrent

#define parse_line _nss_directories_parse_grent

#include "generic.c"
