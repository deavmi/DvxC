#include "../registers.c"

void huisdans(struct CPU* cpu)
{
	printf("huisdans woopee!\n");
}

/* Take the byte and assigns it to the byte-wide register */
void register_assign_byte(struct CPU* cpu)
{
	/* Get the register ID */
	char registerID = get_registerID(cpu->registerFile.instruction);

	/* Get the immediate */
	char immediate = *(((char*)&(cpu->registerFile.instruction))+2);

	/* Calculate the base of the byte registers */
	char* bwrBase = &(cpu->registerFile.a);

	/* TODO: Error check, raise exception elsewise */
	if (is_byte_register(registerID)) {
		/* If the registerID is correct, then copy the immediate
		 * into the register.
		 */
		*(bwrBase+registerID) = immediate;
	} else {
		/* If the registerID is incorrect then
		 * raise an interrupt.
		 */
		interrupt(cpu);
		/* TODO: Add code to set correct interrupt type */
	}
}

void register_assign_short(struct CPU* cpu)
{
	/* Get the register ID */
	char registerID = get_registerID(cpu->registerFile.instruction);

	/* Get the immediate */
	short immediate = *(((short*)&(cpu->registerFile.instruction))+2);

	/* Calculate the base of the short/word registers */
	short* swrBase = &(cpu->registerFile.ae);

	/* TODO: Implement me */
	if (is_word_register(registerID)) {
		/* If the registerID is correct, then copy the immediate
		 * into the register.
		 */
		*(swrBase+registerID) = immediate;
	} else {
		/* If the registerID is incorrect then
		 * raise an interrupt.
		 */
		
//		set_interrupt_s
	}
}

void register_assign_upper(struct CPU* cpu)
{
	/* Get the register ID */
	char registerID = get_registerID(cpu->registerFile.instruction);

	/* Get the immediate */
	char immediate = *((short*)(((char*)&(cpu->registerFile.instruction))+2));

	/* Calculate the base of the double-word registers */
	int* dwwrBase = &(cpu->registerFile.aex);
	
	/* TODO: Implement me */
	if (is_double_word_register(registerID)) {
		
	} else {
		
	}
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
	/* Set the `ip` to the requested address */
	cpu->registerFile.ip = instruction_address;
	/* TODO: Add printf here */
}

void interrupt_return(struct CPU* cpu)
{
	/* Get the address to return to */
	int interrupt_return_address = cpu->registerFile.hex;
	printf("Returning from %u to %u\n", cpu->registerFile.ip, interrupt_return_address);

	/* Set `ip` to register `hex` */
	cpu->registerFile.ip = interrupt_return_address;
}

/* Sets the flag for an interrupt.
 *
 * The `h` register holds the interrupt
 * id.
 */
void interrupt(struct CPU* cpu)
{
	/* Set the interrupt bit in the flags register */
	cpu->registerFile.flags = cpu->registerFile.flags | 2;
}

void interrupt_jump_set(struct CPU* cpu)
{
	/* Determine the interrupt id */
	char interrupt_id = cpu->registerFile.h;
	printf("[Instruction: int]: Interrupt ID: %u\n", interrupt_id);

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
	cpu->registerFile.hex = cpu->registerFile.ip+4;

	/* TODO: Also maybe we should store the instruction before this one ey */

	/* We must transition to a lower ring (TODO: add real and protected mode) */
	if (!is_real_mode(cpu)) {
		printf("[Instruction: int]: We are in protected mode, ring-switch before jump\n");
		ring_0(cpu);
	}

	/* Determine the offset into the vector table */
	/* TODO: Arithmetic like add and subtract actually stay the same for unsigned and two's complement, but anywho */
	/* TODO: also check type casts everywhere, gcc does weird shit sometimes (maybe that was just printf, idk, probs not) */
	unsigned int vector = ((unsigned int)cpu->registerFile.vector_table)+(unsigned int)interrupt_id;

	/* Jump to the vector */
	jump(cpu, vector);
}

void halt(struct CPU* cpu)
{
	/* Halt the CPU */
	cpu->is_active = 0;
	printf("[Instruction: halt]: CPU is_active set to 0\n");
}

void nop()
{
	/* Nop */
	printf("[Instruction: nop]: Doing nothing\n");
}