/*
 * Memory management unit
 *
 * This struct describes the mapping of virtual addresses to physical ones.
 * It also includes the memory map for what physical addresses go to what
 * physical devices.
 */
struct MMU
{
	
};

/* Mermory
 *
 * General container of all the components of the memory module.
 *
 */
struct Memory
{
	/* The memory module's Memory Management Unit */
	struct MMU mmu;

	/* Physical memory */
	char* memory_physical_region;
	long memory_physical_region_length;
};

