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

#ident "$Id: passwd.c,v 1.1 2002/11/18 19:53:21 nalin Exp $"

#include <sys/types.h>
#include <pwd.h>

#define STRUCTURE passwd
#define FILENAME  "passwd"

#define getnam _nss_directories_getpwnam_r
#define getnam_field pw_name

#define getnum _nss_directories_getpwuid_r
#define getnum_type uid_t
#define getnum_field pw_uid

#define setent _nss_directories_setpwent
#define getent _nss_directories_getpwent_r
#define endent _nss_directories_endpwent

#define parser _nss_files_parse_pwent

#include "generic.c"
