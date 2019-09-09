/* This is for testing */
void set_bios(struct CPU* cpu)
{
	/* Huisdans instruction */
	set32(cpu, 68, 257);

	/* Interrupt instruction */
	set32(cpu, 72, 9);

	/* Halt instruction */
	set32(cpu, 76, 11);
}

/* Set the interrupt handlers */
void set_vectors(struct CPU* cpu)
{
	
}

/* Set the vector table base */
void set_vector_table(struct CPU* cpu)
{
	
}

void testing_setup(struct CPU* cpu)
{
	/* Inject bios code */
	set_bios(cpu);

	/* Set the vector table base */
	set_vector_table(cpu, 5);

	/* Set the vectors (and load the code to them) */
	set_vectors(cpu);
}