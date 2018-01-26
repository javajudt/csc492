/*
	Jordan Judt
	CSC 492
	1-26-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("USAGE: %s <filename>\n\n", argv[0]);
		return -1;
	}
	
	int file = open(argv[1], O_RDONLY);
	if (file == -1)
	{
		printf("Error: Could not open the file '%s'\n\n", argv[1]);
		exit(-1);
	}
	
	char buffer;
	ssize_t readSize = 1;
	while(readSize == 1)
	{
		readSize = read(file, &buffer, 1);
		printf("%c", buffer);
	}
	if (readSize == -1)
	{
		printf("Error: Could not read from file '%s'\n\n", argv[1]);
		exit(-1);
	}
	
	int closed = close(file);
	if (closed != 0)
	{
		printf("Warning: Could not close the file '%s'\n\n", argv[1]);
	}
	
	return 0;
}

