/*
	Jordan Judt
	CSC 492
	2-23-2018
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(){
	printf("%s\n", getpwuid(getuid())->pw_name);
	return 0;
}
