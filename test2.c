#include<stdio.h>

int main()
{
	printf("Valu: %u\n", 1&&2); //1
	printf("Valu: %u\n", 1&&1); //1
	printf("Valu: %u\n", 2&&1); //1
	printf("Valu: %u\n", 1&2); //0

	printf("Valu: %u\n", 1&&3); //1
	printf("Valu: %u\n", 1&3); //1
	
	printf("Valu: %u\n", 3&&3); //1
	printf("Valu: %u\n", 3&&0); //0
	printf("Valu: %u\n", 3&&1); //1
	printf("Valu: %u\n", 3&3); //3

	printf("Valu: %u\n", 3&&2); //1
	printf("Valu: %u\n", 2&&3); //1
	printf("Valu: %u\n", 3&2); //2
	printf("Valu: %u\n", 3&4); //0
	
			
	
}