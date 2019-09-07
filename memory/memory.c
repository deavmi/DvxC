/* Memory routines */

#include <sys/mman.h>

char* get_memory(long size)
{
	char* memory_region = (char*)mmap(0, size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS+MAP_PRIVATE, 0, 0);

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

int get_physical_address(struct CPU* cpu, int virtual_address)
{
	/* The physical_address can only change from virtual
	 * if the MMU is tuend on.
	 */
	int physical_address = virtual_address;

	/* Check if we are on protected mode */
	if (is_real_mode(cpu)) {
		/* TODO: Implement me */
	}

	printf("Virtual address: %u\n", virtual_address);
	printf("Physical address: %u\n", physical_address);
	return physical_address;
}

void set32(struct CPU* cpu, unsigned int address, int data)
{
	/* Can also map away and to BIOS, need to add meory map */
	char* base_memory = cpu->memoryModule.memory_physical_region;

	*((int*)(base_memory+address)) = data;
	printf("Stored data %u at address %u\n", data, address);
}

void set16(struct CPU* cpu, unsigned int address, short data)
{
	/* Can also map away and to BIOS, need to add meory map */
	char* base_memory = cpu->memoryModule.memory_physical_region;

	*((short*)(base_memory+address)) = data;
}

void set8(struct CPU* cpu, unsigned int address, char data)
{
	/* Can also map away and to BIOS, need to add meory map */
	char* base_memory = cpu->memoryModule.memory_physical_region;

	*((char*)(base_memory+address)) = data;
}

int fetch32(struct CPU* cpu, unsigned int address)
{
	int memory;

	/* Can also map away and to BIOS, need to add meory map */
	char* base_memory = cpu->memoryModule.memory_physical_region;

	memory = *((int*)(base_memory+address));

	return memory;
}

short fetch16(struct CPU* cpu, unsigned int address)
{
	short memory;

	/* Can also map away and to BIOS, need to add meory map */
	char* base_memory = cpu->memoryModule.memory_physical_region;

	memory = *((short*)(base_memory+address));

	return memory;
}

char fetch8(struct CPU* cpu, unsigned int address)
{
	char memory;

	/* Can also map away and to BIOS, need to add meory map */
	char* base_memory = cpu->memoryModule.memory_physical_region;

	memory = *((char*)(base_memory+address));

	return memory;
}