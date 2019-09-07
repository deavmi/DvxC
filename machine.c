#include "cpu.c"

char emulate()
{
	/* Exit status of the machine run, non-zero if an error occurred */
	char machine_exit_status = 0;

	/* Create a new cpu */
	struct CPU* cpuInstance = new_cpu();
	printf("Created new cpu instance\n");
	
	/* Run machine */
	printf("CPU emulation started\n");
	cpu(cpuInstance);
	
	printf("Emulator ended\n");
	
	return machine_exit_status;	
}