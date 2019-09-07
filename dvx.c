#include <stdio.h>
#include "machine.c"
#include <stdlib.h>

int main()
{
	/* TODO: Get a file for the machine */

	/* Boot the machine */
	printf("Emulation started\n");
	emulate();
	printf("Emulation ended\n");
}