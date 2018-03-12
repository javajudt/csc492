#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char **test = malloc(5);
	test[0] = "0";
	test[1] = "11";
	test[2] = "222";
	test[3] = "3333";
	test[4] = "44444";
	
	int size = sizeof(test)/sizeof(test[0]);
	
	/*
	for (int i = 0; i < size; i++)
	{
		printf("%s", test[i]);
	}*/
	
	
	char *temp[size];
	int j = size-1;
	for (int i = 0; i < size; i++)
	{
		temp[j--] = test[i];
	}
//	free(test);
	test = temp;
	for (int i = 0; i < size; i++)
	{
		printf("%s", test[i]);
	}
}
