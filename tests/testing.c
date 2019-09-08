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

void testing_setup(struct CPU* cpu)
{
	/* Inject bios code */
	set_bios(cpu);
}