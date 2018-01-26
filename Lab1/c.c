/*
	Jordan Judt
	CSC 492
	1-19-2018
*/

#include<stdio.h>

int main()
{
	int n, i, j;
	printf("Enter the number of lines: ");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		int total = n + (i - 1);
		int space = n - i;
		int ast = total - space;
		for (j = 0; j <= space; j++)
		{
			printf(" ");
		}
		for (j = 0; j < ast; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	
	for (i = n-1; i>0; i--)
	{
		int total = n + (i - 1);
		int space = n - i;
		int ast = total - space;
		for (j = 0; j <= space; j++)
		{
			printf(" ");
		}
		for (j = 0; j < ast; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
