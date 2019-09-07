/* Memory routines */

#include <sys/mman.h>

char* get_memory(long size)
{
	char* memory_region = (char*)mmap(0, size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS, 0, 0);

	return memory_region;
}

/* TODO: add argument for memory map */
void initialize_memory(struct CPU* cpu, long size)
{
	/* Allocate memory for the Memory module */
	//struct Memory* memory = (struct Memory*)malloc(sizeof(struct Memory));

	/* Allocate physical memory of the requested length */
	cpu->memoryModule.memory_physical_region_length = size;
	cpu->memoryModule.memory_physical_region = get_memory(cpu->memoryModule.memory_physical_region_length);
}