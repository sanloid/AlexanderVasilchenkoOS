#include <stdio.h>
#include <fcntl.h>

void main(){
	char buffer[100]="";
	int len;
	int fhandle;
	char fname[ ]="file";

	fhandle=open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	printf("%d", fhandle);
	len=read(0, buffer, 80);
	write(fhandle, buffer, len);
	close(fhandle);
}
