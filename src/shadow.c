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

#ident "$Id: shadow.c,v 1.1 2002/11/18 19:53:21 nalin Exp $"

#include <sys/types.h>
#include <shadow.h>

#define STRUCTURE spwd
#define FILENAME  "shadow"

#define getnam _nss_directories_getspnam_r
#define getnam_field sp_namp

#define setent _nss_directories_setspent
#define getent _nss_directories_getspent_r
#define endent _nss_directories_endspent

#define parser _nss_files_parse_spent

#include "generic.c"
