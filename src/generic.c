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

#ident "$Id: generic.c,v 1.3 2002/11/19 00:05:07 nalin Exp $"

#include "../config.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <fnmatch.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <nss.h>

#define CHUNK_SIZE LINE_MAX
#define FALSE 0
#define TRUE (!FALSE)

/* Array of file name patterns we ignore. */
static const char *skip_names[] = {
	"*~",
	"*.rpmsave",
	"*.rpmorig",
	"*.rpmnew",
};

/* Return TRUE if we should ignore the file based on its name. */
static int
skip_file_by_name(const char *filename)
{
	int i;
	for (i = 0; i < sizeof(skip_names) / sizeof(skip_names[0]); i++) {
		if (fnmatch(skip_names[i], filename, 0) == 0) {
			return TRUE;
		}
	}
	return FALSE;
}

/* Read a line from the given file, no matter the length. */
static char *
read_line(FILE *fp)
{
	char *buffer;
	size_t buflen, length;

	buflen = CHUNK_SIZE;
	length = 0;
	buffer = malloc(CHUNK_SIZE);
	if (buffer == NULL) {
		return NULL;
	}
	memset(buffer, 0, buflen);

	while (fgets(buffer + length, buflen - length, fp) != NULL) {
		length = strlen(buffer);
		if (length > 0) {
			if (buffer[length - 1] == '\n') {
				break;
			} else {
				buflen += CHUNK_SIZE;
				buffer = realloc(buffer, buflen);
				if (buffer == NULL) {
					return NULL;
				}
				memset(buffer + length, 0, buflen - length);
			}
		}
	}

	if (strlen(buffer) == 0) {
		free(buffer);
		return NULL;
	}

	if ((length > 0) && (buffer[length - 1] == '\n')) {
		buffer[length - 1] = '\0';
	}

	return buffer;
}

static enum nss_status
getgen(struct STRUCTURE *result,
#ifdef GET_EXTRA_CRITERIA
       GET_EXTRA_CRITERIA,
#endif
       char *buffer, size_t buflen, int *errnop,
       int (*compare)(const void *compare_data, struct STRUCTURE *structure),
       const void *compare_data)
{
	DIR *dir = NULL;
	FILE *fp = NULL;
	struct STRUCTURE structure;
	struct dirent *ent = NULL;
	struct stat st;
	char path[PATH_MAX], *line;

	/* Start reading the directory. */
	dir = opendir(SYSCONFDIR "/" DATABASE ".d");
	if (dir == NULL) {
		*errnop = errno;
		return NSS_STATUS_NOTFOUND;
	}

	/* Iterate over each file in the directory. */
	while ((ent = readdir(dir)) != NULL) {
		/* If the file has a certain name, skip it. */
		if (skip_file_by_name(ent->d_name)) {
			continue;
		}

		/* Figure out the full name of the file. */
		snprintf(path, sizeof(path), SYSCONFDIR "/" DATABASE ".d/%s",
			 ent->d_name);

		/* If we can't open it, skip it. */
		fp = fopen(path, "r");
		if (fp == NULL) {
			continue;
		}

		/* If we can't stat() it, or it's not a regular file or
		 * a symlink, skip it. */
		if ((fstat(fileno(fp), &st) != 0) ||
		    (!S_ISREG(st.st_mode) && !S_ISLNK(st.st_mode))) {
			fclose(fp);
			continue;
		}

		/* Read the next line. */
		while ((line = read_line(fp)) != NULL) {
			/* If we had trouble parsing it, continue. */
			if (parse_line(line, &structure,
				       (void *)buffer, buflen,
				       errnop) == 0) {
				free(line);
				continue;
			}
			/* If it matches, close the file and the directory,
			 * and return the answer. */
			if ((compare(compare_data, &structure) == 0) &&
#ifdef CHECK_EXTRA_CRITERIA
			    CHECK_EXTRA_CRITERIA(&structure) &&
#endif
			    TRUE) {
				*result = structure;
				free(line);
				fclose(fp);
				closedir(dir);
				return NSS_STATUS_SUCCESS;
			}

			/* Free this line. */
			free(line);
		}

		/* Close this file. */
		fclose(fp);
	}

	/* Close this directory. */
	closedir(dir);

	/* Tell the caller that we didn't find anything. */
	return NSS_STATUS_NOTFOUND;
}
#if defined(getnam) && defined(getnam_field)
static int
compare_name(const void *compare_data, struct STRUCTURE *structure)
{
#ifdef getnam_fields
	int i;
	if (structure->getnam_fields != NULL) {
		for (i = 0; structure->getnam_fields[i] != NULL; i++) {
			if (strcmp(structure->getnam_fields[i],
				   (const char *)compare_data) == 0) {
				return 0;
			}
		}
	}
#endif
	return strcmp(structure->getnam_field, (const char *)compare_data);
}
enum nss_status
getnam(const char *name,
#ifdef GET_EXTRA_CRITERIA
       GET_EXTRA_CRITERIA,
#endif
       struct STRUCTURE *result, char *buffer, size_t buflen, int *errnop )
{
	return getgen(result,
#ifdef EXTRA_CRITERIA_NAMES
		      EXTRA_CRITERIA_NAMES,
#endif
		      buffer, buflen, errnop,
		      compare_name, (const void*) name);
}
#endif
#if defined(getnum) && defined(getnum_type) && defined(getnum_field)
static int
compare_number(const void *compare_data, struct STRUCTURE *structure)
{
	return (structure->getnum_field != (getnum_type) compare_data);
}
enum nss_status
getnum(getnum_type number,
#ifdef GET_EXTRA_CRITERIA
       GET_EXTRA_CRITERIA,
#endif
       struct STRUCTURE *result, char *buffer, size_t buflen, int *errnop )
{
	return getgen(result,
#ifdef EXTRA_CRITERIA_NAMES
		      EXTRA_CRITERIA_NAMES,
#endif
		      buffer, buflen, errnop,
		      compare_number, (const void*) number);
}
#endif
#if defined(setent) && defined(getent) && defined(endent)

static pthread_mutex_t enumeration_lock = PTHREAD_MUTEX_INITIALIZER;
#define LOCK() pthread_mutex_lock(&enumeration_lock)
#define UNLOCK() pthread_mutex_unlock(&enumeration_lock)
static DIR *dir = NULL;
static FILE *fp = NULL;

enum nss_status
endent(void)
{
	/* Close the directory and the current file. */
	LOCK();
	if (fp != NULL) {
		fclose(fp);
		fp = NULL;
	}
	if (dir != NULL) {
		closedir(dir);
		dir = NULL;
	}
	UNLOCK();
	return NSS_STATUS_UNAVAIL;
}
enum nss_status
setent(int stayopen)
{
	/* Close and reopen the directory. */
	endent();
	LOCK();
	dir = opendir(SYSCONFDIR "/" DATABASE ".d");
	UNLOCK();
	return (dir == NULL) ? NSS_STATUS_UNAVAIL : NSS_STATUS_SUCCESS;
}
enum nss_status
getent(struct STRUCTURE *result, char *buffer, size_t buflen, int *errnop)
{
	char path[PATH_MAX], *line;
	struct dirent *ent;
	struct stat st;
	struct STRUCTURE structure;

	LOCK();

	/* If we don't have a current directory, try to reset. */
	if (dir == NULL) {
		setent(TRUE);
		/* If we couldn't open the directory, then we'd better just
		 * give up now. */
		if (dir == NULL) {
			UNLOCK();
			return NSS_STATUS_NOTFOUND;
		}
	}

	do {
		/* If we don't have a current file, try to open the next file
		 * in the directory. */
		if ((fp == NULL) || feof(fp)) {
			if (fp != NULL) {
				fclose(fp);
				fp = NULL;
			}

			do {
				/* Read the next entry in the directory. */
				ent = readdir(dir);
				if (ent == NULL) {
					closedir(dir);
					dir = NULL;
					continue;
				}

				/* If the file has a certain name, skip it. */
				if (skip_file_by_name(ent->d_name)) {
					continue;
				}

				/* Formulate the full path name and try to
				 * open it. */
				snprintf(path, sizeof(path),
					 SYSCONFDIR "/" DATABASE ".d/%s",
					 ent->d_name);
				fp = fopen(path, "r");

				/* If we failed to open the file, move on. */
				if (fp == NULL) {
					continue;
				}

				/* If we can't stat() the file, move on. */
				if (fstat(fileno(fp), &st) != 0) {
					fclose(fp);
					fp = NULL;
					continue;
				}

				/* If the file isn't normal or a symlink,
				 * move on. */
				if (!S_ISREG(st.st_mode) &&
				    !S_ISLNK(st.st_mode)) {
					fclose(fp);
					fp = NULL;
					continue;
				}
			} while ((dir != NULL) && (fp == NULL));
		}

		/* If we're out of data, return NOTFOUND. */
		if ((dir == NULL) || (fp == NULL)) {
			UNLOCK();
			return NSS_STATUS_NOTFOUND;
		}

		/* Read a line from the file. */
		line = read_line(fp);
		if (line == NULL) {
			fclose(fp);
			fp = NULL;
			continue;
		}

		/* Try to parse the line. */
		if (parse_line(line, &structure,
			       (void *) buffer, buflen,
			       errnop) != 0) {
			free(line);
			*result = structure;
			UNLOCK();
			return NSS_STATUS_SUCCESS;
		}

		/* Try the next entry. */
		free(line);
	} while (1);

	/* We never really get here, but oh well. */
	UNLOCK();
	return NSS_STATUS_UNAVAIL;
}
#endif

#ifdef IMPLEMENT_MAIN
int
main(int argc, char **argv)
{
	struct passwd pwd;
	char buffer[LINE_MAX];
	int error;
	if (getnum(500, &pwd, buffer, sizeof(buffer),
		   &error) == NSS_STATUS_SUCCESS) {
		printf("%s:%ld\n", pwd.pw_name, (long) pwd.pw_uid);
	}
	while (getent(&pwd, buffer, sizeof(buffer),
		      &error) == NSS_STATUS_SUCCESS) {
		printf("%s:%ld\n", pwd.pw_name, (long) pwd.pw_uid);
	}
	return 0;
}
#endif
