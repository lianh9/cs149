#include "apue.h"

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
	{
        /** Write to stderr the number of bytes that were read from stdin each time.*/
		fprintf(stderr,"Number of bytes that were read from stdin: %d\n", n);


		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");


	}
	if (n < 0)
		err_sys("read error");



	exit(0);
}

