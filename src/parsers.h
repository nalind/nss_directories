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

#ident "$Id: parsers.h,v 1.1 2002/11/18 19:53:21 nalin Exp $"

#ifndef parsers_h
#define parsers_h

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <netdb.h>

struct parser_data;

extern int _nss_files_parse_pwent(char *line, struct passwd *result,
				  struct parser_data *data, size_t datalen,
				  int *errnop);
extern int _nss_files_parse_grent(char *line, struct group *result,
				  struct parser_data *data, size_t datalen,
				  int *errnop);
extern int _nss_files_parse_spent(char *line, struct spwd *result,
				  struct parser_data *data, size_t datalen,
				  int *errnop);
extern int _nss_files_parse_servent(char *line, struct servent *result,
				    struct parser_data *data, size_t datalen,
				    int *errnop);
extern int _nss_files_parse_protoent(char *line, struct protoent *result,
				     struct parser_data *data, size_t datalen,
				     int *errnop);

#endif
