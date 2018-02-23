/*
	Jordan Judt
	CSC 492
	2-16-2018
*/

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void printTime(time_t timeval)
{
	char buff[14];
	strftime(buff, 14, "%b %d %H:%M", localtime(&timeval));
	printf("%s ", buff);
}

void printFileInfo(char dirname[])
{
	struct stat infobuf;
	
	if (stat(dirname, &infobuf) == -1)
		perror(dirname);
	else
	{
		printf("%o ", infobuf.st_mode);
		printf("%ld ", infobuf.st_nlink);
		printf("%4d ", infobuf.st_uid);
		printf("%4d ", infobuf.st_gid);
		printf("%4ld ", infobuf.st_size);
		printTime(infobuf.st_mtim.tv_sec);
	}
}

void printList(char dirname[])
{
	DIR *dir_ptr; //the directory
	struct dirent * direntp; //each entry
	
	if ((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	else
	{
		while ((direntp = readdir(dir_ptr)) != NULL)
		{
			printFileInfo(dirname);
			printf("%s\n", direntp->d_name);
		}
		closedir(dir_ptr);
	}
}

int main(int argc, char *argv[]){
	if (argc == 1)
		printList(".");
	else if (argc == 2)
	{
		while (--argc)
		{
			printf("%s:\n", *++argv);
			printList(*argv);
		}
	}
	else
	{
		printf("USAGE: %s [directory]", argv[0]);
		return 1;
	}
	return 0;
}

