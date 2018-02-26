/*
	Jordan Judt
	CSC 492
	3-2-2018
*/

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

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




void printNames(char dirname[], bool includeDot)
{
	DIR *dir_ptr; //the directory
	struct dirent * direntp; //each entry
	
	if ((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	else
	{
		while ((direntp = readdir(dir_ptr)) != NULL)
		{
			printf("%s  ", direntp->d_name);
		}
		closedir(dir_ptr);
	}
}


/*
Prints the proper usage of the 'myls' command.
Used when the command has invalid arguments.
*/
int usage(char* name)
{
	printf("USAGE: %s [directory]", name); // TODO update usage
	return 1;
}

/*
Main method which parses the arguments and calls print methods appropriately.
*/
// TODO accept path argument
int main(int argc, char *argv[]){
	if (argc == 1)
		printNames(".", false);
	else if (argc == 2)
	{
		if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--all") == 0)
		{
			printf("-a");
		}
		else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--inode") == 0)
		{
			printf("-i");
		}
		else if (strcmp(argv[1], "-l") == 0)
		{
			printf("-l");
		}
		else if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "--reverse") == 0)
		{
			printf("-r");
		}
		else if (strcmp(argv[1], "-S") == 0)
		{
			printf("-S");
		}
		else if (strcmp(argv[1], "-t") == 0)
		{
			printf("-t");
		}
		else if (strcmp(argv[1], "-R") == 0 || strcmp(argv[1], "--recursive") == 0)
		{
			printf("-R");
		}
		else
		{
			return usage(argv[0]);
		}
		//while (--argc)
//		{
	//		printf("%s:\n", *++argv);
		//	printList(*argv);
//		}
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-l") == 0 && (strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "--human-readable") == 0))
		{
			printf("-l -h");
		}
	}
	else
	{
		return usage(argv[0]);
	}
	
	printf("\n");
	return 0;
}

