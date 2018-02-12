#include <stdio.h>
int main()
{
    int var = 789;
    int *ptr1;
    int **ptr2;
    ptr1 = &var;
    ptr2 = &ptr1;
    
