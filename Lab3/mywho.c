/*
	Jordan Judt
	CSC 492
	2-2-2018
*/

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void showtime(time_t timeval)
{
	char buff[17];
	strftime(buff, 17, "%Y-%m-%d %H:%M", localtime(&timeval));
	printf("%20.17s ", buff);
}

void show_info(struct utmp *utbufp)
{
	printf("%s ", utbufp->ut_name);
	printf("%s\t", utbufp->ut_line);
	showtime(utbufp->ut_time);
	printf("(%s)", utbufp->ut_host);
}

int main()
{
	struct utmp utbuf;
	int utmpfd;
	
	if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	
	while(read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf));
	show_info(&utbuf);
	close(utmpfd);
	printf("\n");
	return 0;
}
