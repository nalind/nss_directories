#include <sys/types.h>
#include <errno.h>
#include <nss.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
	char *buf;
	size_t size = 2;
	int result;
	struct passwd passwd, *pwd = NULL;

	__nss_configure_lookup ("passwd", "directories");

	buf = malloc(size);
	setpwent();
	do {
		pwd = NULL;
		result = getpwent_r(&passwd, buf, size, &pwd);
		printf("%d: ", result);
		switch (result) {
		case 0:
			printf("%s\n", pwd->pw_name);
			break;
		case ERANGE:
			printf("%d is not enough, error = %s\n", size,
			       strerror(errno));
			size++;
			free(buf);
			buf = malloc(size);
			result = 0;
			break;
		default:
			printf("failed (%s)\n", strerror(result));
			_exit(1);
			break;
		}
	} while (result == 0);
	endpwent();
	return 0;
}
