#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

void main()
{
	char fname[] = "file";
	char buffer[100];
	int fhandle;
	int cb;
	int boolflag = 1;
	struct flock lock = {F_WRLCK, SEEK_SET, 0, 0};
	fhandle = open(fname, O_RDWR, 0600);

	while (fcntl(fhandle, F_SETLK, &lock) == -1)
	{
		if (boolflag == 1)
		{
			printf("%s\n", RED);
			write(1, "Error\n", 6);
			boolflag = 0;
		}
		sleep(3);
	}

	printf("%s\n", GREEN);
	cb = read(fhandle, buffer, 80);
	write(1, buffer, cb);
	sleep(10);
	close(fhandle);
}
