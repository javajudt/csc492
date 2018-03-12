/*
	Jordan Judt
	CSC 492 - Programming 1
	3-5-2018
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

//flag definitions
bool ALL		= false;
bool HUMAN		= false;
bool INODE		= false;
bool LONG		= false;
bool REVERSE	= false;
bool SIZE		= false;
bool TIME		= false;
bool RECURSIVE	= false;

// Converts a large number of bytes to a human-readable string.
void convertSizeToReadable(char *size)
{
	char **endbuf;
	long l = strtol(size, endbuf, 10);
	
	int i = 0;
	while (l >= 1024)
	{
		l /= 1024;
		i++;
	}
	
	char suffix[] = "\0KMGTP"; // Suffix definitions for size
	snprintf(size, 100, "%ld%c", l, suffix[i]);
}

// Converts raw file permissions to a human-readable string.
void convertModeToReadable(char *buf, mode_t mode)
{
	char dir = (mode & S_IFDIR) ? 'd' : '-';
	char ru = (mode & S_IRUSR) ? 'r' : '-';
	char wu = (mode & S_IWUSR) ? 'w' : '-';
	char xu = (mode & S_IXUSR) ? 'x' : '-';
	char rg = (mode & S_IRGRP) ? 'r' : '-';
	char wg = (mode & S_IWGRP) ? 'w' : '-';
	char xg = (mode & S_IXGRP) ? 'x' : '-';
	char ro = (mode & S_IROTH) ? 'r' : '-';
	char wo = (mode & S_IWOTH) ? 'w' : '-';
	char xo = (mode & S_IXOTH) ? 'x' : '-';
	
	snprintf(buf, 11, "%c%c%c%c%c%c%c%c%c%c", dir, ru, wu, xu, rg, wg, xg, ro, wo, xo);
}

// Reverses the order of a string array that has the given number of elements.
void reverse(char **strs, int strc)
{
	int i = 0;
	int j = strc-1;
	while (j > i)
	{
		char *temp = strs[i];
		strs[i] = strs[j];
		strs[j] = temp;
		i++;
		j--;
	}
}

// Uses Bubble Sort to sort the printBuf array based on the elements in the sortBy array. Both arrays have strc number of elements.
void sort(char **printBuf, char **sortBy, int strc)
{
	if (SIZE || TIME) //sort by file size or modification time
	{
		for (int j = 0; j < strc-1; j++)
		{
			bool sorted = true;
			for (int i = 0; i < strc-1; i++)
			{
				long l1 = strtol(sortBy[i], NULL, 10);
				long l2 = strtol(sortBy[i+1], NULL, 10);
				if (l2 > l1)
				{
					char *temp = sortBy[i];
					sortBy[i] = sortBy[i+1];
					sortBy[i+1] = temp;
					
					temp = printBuf[i];
					printBuf[i] = printBuf[i+1];
					printBuf[i+1] = temp;
					
					sorted = false;
				}
			}
			if (sorted) break;
		}
	}
	else //sort by name
	{
		for (int j = 0; j < strc-1; j++)
		{
			bool sorted = true;
			for (int i = 0; i < strc-1; i++)
			{
				if (strcmp(sortBy[i], sortBy[i+1]) > 0)
				{
					char *temp = sortBy[i];
					sortBy[i] = sortBy[i+1];
					sortBy[i+1] = temp;
					
					temp = printBuf[i];
					printBuf[i] = printBuf[i+1];
					printBuf[i+1] = temp;
					
					sorted = false;
				}
			}
			if (sorted) break;
		}
	}
	
	if (REVERSE) //reverse order
		reverse(printBuf, strc);
}

// Gets the file info and appends it to the given buffer.
void printFileInfo(int *printedFiles, char name[], char **printBuf, char **sortBy, struct stat *statBuf)
{
	if (name[0] != '.' || ALL)
	{
		int remainingBytes = 100;
		char *info = malloc(remainingBytes);
		remainingBytes--;
	
		if (INODE) // print inode
		{
			char inodeBuf[7];
			snprintf(inodeBuf, 7, "%5lu ", statBuf->st_ino);
			strncat(info, inodeBuf, remainingBytes);
			remainingBytes -= strlen(inodeBuf)+1;
		}
		if (LONG) // long listing
		{
			// Get RWX modes
			char modeBuf[11];
			convertModeToReadable(modeBuf, statBuf->st_mode);
			strncat(strncat(info, modeBuf, remainingBytes), " ", 1);
			remainingBytes -= strlen(modeBuf)+1;
			
			// Get links
			char linkBuf[11];
			snprintf(linkBuf, 11, "%ld ", statBuf->st_nlink);
			strncat(info, linkBuf, remainingBytes);
			remainingBytes -= strlen(linkBuf);
			
			// Get user name
			char *user = getpwuid(statBuf->st_uid)->pw_name;
			strncat(strncat(info, user, remainingBytes), " ", 1);
			remainingBytes -= strlen(user)+1;
			
			// Get group name
			char *group = getgrgid(statBuf->st_gid)->gr_name;
			strncat(strncat(info, group, remainingBytes), " ", 1);
			remainingBytes -= strlen(group)+1;
			
			// Get file size
			char sizeBuf[10];
			snprintf(sizeBuf, 10, "%4ld", statBuf->st_size);
			if (HUMAN)
				convertSizeToReadable(sizeBuf);
			strncat(strncat(info, sizeBuf, remainingBytes), " ", 1);
			remainingBytes -= strlen(sizeBuf)+1;
		
			// Get time
			char timeBuf[14];
			strftime(timeBuf, 14, "%b %d %H:%M", localtime(&(statBuf->st_mtim.tv_sec)));
			strncat(strncat(info, timeBuf, remainingBytes), " ", 1);
			remainingBytes -= strlen(timeBuf)+1;
		}
		
		// Get file name
		strncat(info, name, remainingBytes);
		remainingBytes -= strlen(name);
		
		// Get value for sorting
		if (SIZE) //sort by file size
		{
			char buf[20];
			snprintf(buf, 20, "%ld", statBuf->st_size);
			sortBy[*printedFiles] = buf;
		}
		else if (TIME) //sort by modification time
		{
			char buf[20];
			snprintf(buf, 20, "%ld", statBuf->st_mtim.tv_sec);
			sortBy[*printedFiles] = buf;
		}
		else //sort by name
			sortBy[*printedFiles] = name;
		
		printBuf[(*printedFiles)++] = info; //add file info to print buffer
	}
}

// Kills the program with an error status.
void dieWithError(char *s)
{
	perror(s);
	exit(errno);
}

int main(int argc, char *argv[])
{
	// Parse user-defined options into flags
	int fileCount = 0;
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
			ALL = true;
		else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--human-readable") == 0)
			HUMAN = true;
		else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--inode") == 0)
			INODE = true;
		else if (strcmp(argv[i], "-l") == 0)
			LONG = true;
		else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--reverse") == 0)
			REVERSE = true;
		else if (strcmp(argv[i], "-S") == 0)
			SIZE = true;
		else if (strcmp(argv[i], "-t") == 0)
			TIME = true;
		else if (strcmp(argv[i], "-R") == 0 || strcmp(argv[i], "--recursive") == 0)
			RECURSIVE = true;
		else
			fileCount++;
	}

	// Parse user-defined directory(ies) and file(s)
	int totalFiles = fileCount;
	char *files[fileCount];
	while (fileCount != 0)
	{
		if (strncmp(argv[fileCount], "-", 1) != 0)
		{
			files[fileCount-1] = argv[fileCount];
			fileCount--;
		}
	}
	
	// No files were specified, so mark the current directory
	if (totalFiles == 0)
	{
		char *file[] = {"."};
		*files = *file;
		totalFiles++;
	}
	
	// Print info for each given file/directory
	int printedFiles = 0;
	char **printBuf = malloc(1000000);
	char **sortBy = malloc(1000000);
	for (int i = 0; i < totalFiles; i++)
	{
		// Get file info
		struct stat statBuf;
		if (lstat(files[i], &statBuf) == -1)
			dieWithError(files[i]);
		
		// File is a directory; list info about all files in it
		if (S_ISDIR(statBuf.st_mode))
		{
			struct dirent *dirEntry; //entry in directory
			DIR *directory; //the directory
	
			if ((directory = opendir(files[i])) == NULL)
				dieWithError(files[i]);
			
			errno = 0;
			// Loop through all files in the directory
			while ((dirEntry = readdir(directory)) != NULL)
			{
				if (errno != 0)
					dieWithError("readdir");
				
				char *name = dirEntry->d_name;
				char pathBuf[256];
				snprintf(pathBuf, sizeof(pathBuf), "%s/%s", files[i], name);
				if (lstat(pathBuf, &statBuf) == -1)
					dieWithError(files[i]);
				
				printFileInfo(&printedFiles, name, printBuf, sortBy, &statBuf);
			}
			
			if (closedir(directory) == -1)
				dieWithError("closedir");
		}
		// File is not a directory; list info about this file
		else
		{
			char *name = files[i];
			printFileInfo(&printedFiles, name, printBuf, sortBy, &statBuf);
		}
	}
	
	sort(printBuf, sortBy, printedFiles); //sort the file info

	for (int i = 0; i < printedFiles; i++)
	{
		if (i > 0) // Separate file info in the console
		{
			if (LONG) //separate by newline if -l; otherwise 2 spaces
				printf("\n");
			else
				printf("  ");
		}
	
		printf("%s", printBuf[i]);
	}
	
	//free allocated memory
	free(printBuf);
	free(sortBy);
	
	printf("\n");
	return 0;
}

