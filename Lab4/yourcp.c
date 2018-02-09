/*
	Jordan Judt
	CSC 492
	2-9-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("USAGE: %s <path_to_original> <path_to_destination>\n\n", argv[0]);
		return -1;
	}
	
	int origFile = open(argv[1], O_RDONLY);
	if (origFile == -1)
	{
		printf("Error: Could not open the file '%s'\n\n", argv[1]);
		exit(-1);
	}
	
	// used open instead of creat so I could specify permissions (creat defaults to 100)
	int destFile = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0664);
	if (destFile == -1)
	{
		printf("Error: Could not create the file '%s'\n\n", argv[2]);
		exit(-1);
	}
	
	char buffer;
	ssize_t readSize = 1;
	while(readSize == 1)
	{
		readSize = read(origFile, &buffer, 1);
		if (readSize == -1)
		{
			printf("Error: Could not read from file '%s'\n\n", argv[1]);
			exit(-1);
		}
		
		if (write(destFile, &buffer, 1) == -1)
		{
			printf("Error: Could not write to file '%s'\n\n", argv[2]);
			exit(-1);
		}
	}
	
	if (close(origFile) != 0)
		printf("Warning: Could not close the original file '%s'\n\n", argv[1]);
	if (close(destFile) != 0)
		printf("Warning: Could not close the destination file '%s'\n\n", argv[2]);
	
	return 0;
}


