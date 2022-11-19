#include <stdio.h>
#include <fcntl.h>

void main(){
	int firstHandle, duppedHandle, secondHandle, thirdHandle, cb, len;
	char fname[ ]="file", buffer[7]="";	

	len = strlen(buffer);
	
	firstHandle = open(fname, O_RDONLY);
	duppedHandle = dup(firstHandle);	
	thirdHandle = open(fname, O_RDONLY);
	printf("%d", firstHandle);
	printf("%s", "\n");	
	printf("%d", duppedHandle);
	printf("%s", "\n");	
	printf("%d", thirdHandle);
	printf("%s", "\n");

	lseek(duppedHandle, 10, SEEK_SET);
	cb=read(firstHandle, buffer, 7);	
	write(1, buffer, cb);
	printf("%s", "\n");	
	
	cb=read(duppedHandle, buffer, 7);
	write(1, buffer, cb);
	printf("%s", "\n");

	cb=read(thirdHandle, buffer, 7);	
	write(1, buffer, cb);
	printf("%s", "\n");
}
