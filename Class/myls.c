#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void fileInfo(char dirname[])
{
	struct stat infobuf;
	struct timespec timebuf;
	
	if (stat(dirname, &infobuf) == -1)
		perror(dirname);
	else
	{
		
		printf("   mode: %o\n", infobuf.st_mode);
		printf("  links: %ld\n", infobuf.st_nlink);
		printf("   user: %d\n", infobuf.st_uid);
		printf("  group: %d\n", infobuf.st_gid);
		printf("   size: %ld\n", infobuf.st_size);
		printf("modtime: %ld\n", infobuf->st_mtim);
		printf("   name: %s\n", dirname);
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
			printf("%s\n", direntp->d_name);
		closedir(dir_ptr);
	}
}

int main(int argc, char *argv[]){
	if (argc != 1 || argc != 2)
	{
		printf("USAGE: %s [directory]", argv[0]);
	}

	if (argc == 1)
		printList(".");
	else
		while (--argc)
		{
			printf("%s:\n", *++argv);
			printList(*argv);
		}
}

