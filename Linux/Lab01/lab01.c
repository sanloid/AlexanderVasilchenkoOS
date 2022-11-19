#include <stdio.h>

void main() {
	int cb;
	char buffer[100]="This is readed... ";

if(isatty(0) != 0){
	write(2,"Enter\n",6); 
	cb=read(0, buffer+18, 80);
	cb += 18;
	write(1, buffer, cb);
}	
else { 
	cb=read(1, buffer+18, 80);
	cb += 18;
	write(1, buffer, cb);
}
}
