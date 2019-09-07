/* Take the byte and assigns it to the byte-wide register */
void register_assign_byte(struct CPU* cpu)
{
	/* Get the register ID */
	char registerID = *(((char*)&(cpu->registerFile.instruction))+1);

	/* Get the immediate */
	char immediate = *(((char*)&(cpu->registerFile.instruction))+2);

	/* TODO: Find out struct packing for nicer way to do this */
}

void register_assign_short(struct CPU* cpu)
{
	/* Get the register ID */
	char registerID = *(((char*)&(cpu->registerFile.instruction))+1);

	/* Get the immediate */
	short immediate = *(((short*)&(cpu->registerFile.instruction))+2);
}

void register_assign_upper(struct CPU* cpu)
{
	/* Get the register ID */
	char registerID = *(((char*)&instruction)+1);

	/* Get the immediate */
	char immediate = *((short*)(((char*)&instruction)+2));
}

void ring_0(struct CPU* cpu)
{
	/* TODO: Implement ring lowering */
	printf("Lowered to ring 0\n");
}

void ring_1(struct CPU* cpu)
{
	/* TODO: Implement ring raising */
	printf("Raised to ring 1\n");
}

void jump(struct CPU* cpu, int instruction_address)
{
	cpu->registerFile.ip = instruction_address;
}

void interrupt_return(struct CPU* cpu)
{
	/* Get the address to return to */
	int interrupt_return_address = cpu->registerFile.hex;
	printf("Returning from %u to %u\n", cpu->registerFile.ip, interrupt_return_address);

	/* Set `ip` to register `hex` */
	cpu->registerFile.ip = interrupt_return_address;
}

void interrupt(struct CPU* cpu)
{
	/* Determine the interrupt id */
	char interrupt_id = cpu->registerFile.interrupt_register;
	printf("Interrupt ID: %u\n", interrupt_id);

	/* We must save the address of the currently
	 * executing instruction, a.k.a., the `int`
	 * instruction and add 4 to it so that we can
	 * jump out of the interrupt to the instruction
	 * that followed the `int` instruction to resume
	 * program progress.
	 */

	/* TODO: Yeah I would like it that we store this, we need a special iret
	 * anywho for protected mode reasons.
	 */
	 

	/* We must transition to a lower ring (TODO: add real and protected mode) */
	if (!is_real_mode(cpu)) {
		printf("We are in protected mode, ring-switch before jump\n");
		ring_0(cpu);
	}

	/* Determine the offset into the vector table */
	/* TODO: Arithmetic like add and subtract actually stay the same for unsigned and two's complement, but anywho */
	/* TODO: also check type casts everywhere, gcc does weird shit sometimes (maybe that was just printf, idk, probs not) */
	unsigned int vector = ((unsigned int)cpu->registerFile.vector_table)+(unsigned int)interrupt_id;

	/* Jump to the vector */
	jump(cpu, vector);
}

void interrupt_return

void halt(struct CPU* cpu)
{
	/* Halt the CPU */
	cpu->is_active = 0;
}