/* Copyright (C) 1991, 1996, 1997, 1998, 1999 Free Software Foundation, Inc.
   This file is assembled from parts of the GNU C Library:
     pwd/fgetpwent_r.c
     grp/fgetgrent_r.c
     shadow/sgetspent_r.c

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include <shadow.h>

#define libc_hidden_def(ignored)
#define _nss_files_parse_ _nss_directories_parse_

/******************************************************************************/
#undef  STRUCTURE
#undef  ENTNAME
#undef  FALSE
#undef  parser_data
#undef  TRAILING_LIST_MEMBER
#undef  TRAILING_LIST_PARSER
#undef  TRAILING_LIST_SEPARATOR_P

/* Define a line parsing function using the common code
   used in the nss_files module.  */

#define STRUCTURE	passwd
#define ENTNAME		pwent
#define parser_data     pwent_data

#include "files-parse.c"
LINE_PARSER
(,
 STRING_FIELD (result->pw_name, ISCOLON, 0);
 if (line[0] == '\0'
     && (result->pw_name[0] == '+' || result->pw_name[0] == '-'))
   {
     /* This a special case.  We allow lines containing only a `+' sign
	since this is used for nss_compat.  All other services will
	reject this entry later.  Initialize all other fields now.  */
     result->pw_passwd = NULL;
     result->pw_uid = 0;
     result->pw_gid = 0;
     result->pw_gecos = NULL;
     result->pw_dir = NULL;
     result->pw_shell = NULL;
   }
 else
   {
     STRING_FIELD (result->pw_passwd, ISCOLON, 0);
     if (result->pw_name[0] == '+' || result->pw_name[0] == '-')
       {
	 INT_FIELD_MAYBE_NULL (result->pw_uid, ISCOLON, 0, 10, , 0)
	 INT_FIELD_MAYBE_NULL (result->pw_gid, ISCOLON, 0, 10, , 0)
       }
     else
       {
	 INT_FIELD (result->pw_uid, ISCOLON, 0, 10,)
	 INT_FIELD (result->pw_gid, ISCOLON, 0, 10,)
       }
     STRING_FIELD (result->pw_gecos, ISCOLON, 0);
     STRING_FIELD (result->pw_dir, ISCOLON, 0);
     result->pw_shell = line;
   }
 )

/******************************************************************************/
#undef  STRUCTURE
#undef  ENTNAME
#undef  FALSE
#undef  parser_data
#undef  TRAILING_LIST_MEMBER
#undef  TRAILING_LIST_PARSER
#undef  TRAILING_LIST_SEPARATOR_P

/* Define a line parsing function using the common code
   used in the nss_files module.  */

#define STRUCTURE	group
#define ENTNAME		grent
#define parser_data     grent_data

#define TRAILING_LIST_MEMBER		gr_mem
#define TRAILING_LIST_SEPARATOR_P(c)	((c) == ',')
#include "files-parse.c"
LINE_PARSER
(,
 STRING_FIELD (result->gr_name, ISCOLON, 0);
 if (line[0] == '\0'
     && (result->gr_name[0] == '+' || result->gr_name[0] == '-'))
   {
     result->gr_passwd = NULL;
     result->gr_gid = 0;
   }
 else
   {
     STRING_FIELD (result->gr_passwd, ISCOLON, 0);
     if (result->gr_name[0] == '+' || result->gr_name[0] == '-')
       INT_FIELD_MAYBE_NULL (result->gr_gid, ISCOLON, 0, 10, , 0)
     else
       INT_FIELD (result->gr_gid, ISCOLON, 0, 10,)
   }
 )

/******************************************************************************/
#undef  STRUCTURE
#undef  ENTNAME
#undef  FALSE
#undef  parser_data
#undef  TRAILING_LIST_MEMBER
#undef  TRAILING_LIST_PARSER
#undef  TRAILING_LIST_SEPARATOR_P

/* Define a line parsing function using the common code
   used in the nss_files module.  */

#define STRUCTURE	spwd
#define ENTNAME		spent
#define parser_data     spent_data

/* Predicate which always returns false, needed below.  */
#define FALSE(arg) 0

#include "files-parse.c"
LINE_PARSER
(,
 STRING_FIELD (result->sp_namp, ISCOLON, 0);
 if (line[0] == '\0'
     && (result->sp_namp[0] == '+' || result->sp_namp[0] == '-'))
   {
     result->sp_pwdp = NULL;
     result->sp_lstchg = 0;
     result->sp_min = 0;
     result->sp_max = 0;
     result->sp_warn = -1l;
     result->sp_inact = -1l;
     result->sp_expire = -1l;
     result->sp_flag = ~0ul;
   }
 else
   {
     STRING_FIELD (result->sp_pwdp, ISCOLON, 0);
     INT_FIELD_MAYBE_NULL (result->sp_lstchg, ISCOLON, 0, 10, (long int),
			   (long int) -1);
     INT_FIELD_MAYBE_NULL (result->sp_min, ISCOLON, 0, 10, (long int),
			   (long int) -1);
     INT_FIELD_MAYBE_NULL (result->sp_max, ISCOLON, 0, 10, (long int),
			   (long int) -1);
     while (isspace (*line))
       ++line;
     if (*line == '\0')
       {
	 /* The old form.  */
	 result->sp_warn = -1l;
	 result->sp_inact = -1l;
	 result->sp_expire = -1l;
	 result->sp_flag = ~0ul;
       }
     else
       {
	 INT_FIELD_MAYBE_NULL (result->sp_warn, ISCOLON, 0, 10, (long int),
			       (long int) -1);
	 INT_FIELD_MAYBE_NULL (result->sp_inact, ISCOLON, 0, 10, (long int),
			       (long int) -1);
	 INT_FIELD_MAYBE_NULL (result->sp_expire, ISCOLON, 0, 10, (long int),
			       (long int) -1);
	 if (*line != '\0')
	   INT_FIELD_MAYBE_NULL (result->sp_flag, FALSE, 0, 10,
				 (unsigned long int), ~0ul)
	 else
	   result->sp_flag = ~0ul;
       }
   }
 )
