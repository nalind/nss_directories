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

/* External parsers. */

#ident "$Id: parsers.h,v 1.2 2002/11/19 00:05:07 nalin Exp $"

#ifndef parsers_h
#define parsers_h

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>

struct pwent_data;
struct grent_data;
struct spent_data;

int _nss_directories_parse_pwent(char *line, struct passwd *result,
				 struct pwent_data *data, size_t datalen,
				 int *errnop);
int _nss_directories_parse_grent(char *line, struct group *result,
				 struct grent_data *data, size_t datalen,
				 int *errnop);
int _nss_directories_parse_spent(char *line, struct spwd *result,
				 struct spent_data *data, size_t datalen,
				 int *errnop);

#endif
