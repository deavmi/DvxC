#include "../registers.c"
#include "misc.c"
#include "../constants.h"

/* This is an instruction for if she ever says yes,
 * that is, when I put my big-boy pants on and actually
 * ask her <3.
 */
void huisdans(struct CPU* cpu)
{
	/* Bruh oomblik */
	printf("huisdans woopee!\n");
}

/* Store the value in a given register into memory
 * at the given address by the value of the other
 * given register.
 */
void store(struct CPU* cpu)
{
	/* TODO: Add this */
	
}

/* Load the value from memory at the address given
 * by the register into the register given.
 */
void load(struct CPU* cpu)
{
	/* TODO: Add this */
	
}

/* Copy value from one register to another register.
 */
void copy(struct CPU* cpu)
{
	/* Get both register IDs */
	char registerID_source = get_registerID(cpu->registerFile.instruction);
	char registerID_destination = get_registerID_secondary(cpu->registerFile.instruction);

	/* Determine the size of the first register (source) */
	enum registerType register_source_type = get_register_type(registerID_source);

	/* Determine the size of the second register (destination) */
	enum registerType register_destination_type = get_register_type(registerID_source);

	/* Ensure both registers (source and destination) are of the same size */
	if (register_source_type == register_destination_type) {
		/*  Get the copy function for the specific register type */
		void (*copy_function)(struct CPU*, char, char) = get_copy_function(register_source_type);

		/* Call the copy function */
		copy_function(cpu, registerID_source, registerID_destination);
	} else {
		/* TODO: Raise exception interrupt here */
	}

	/* TODO: Implement this */

	/* Do the copy */
	/* Implement this */
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
		/* If the registerID is incorrect for
		 * this instruction then raise an
		 * interrupt.
		 */
		interrupt(cpu);

		/* Set the interrupt id */
		set_interrupt_id(cpu, INTERRUPT_INVALID_REGISTER_ID);
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
		/* If the registerID is incorrect for
		 * this instruction then raise an
		 * interrupt.
		 */
		interrupt(cpu);

		/* Set the interrupt id */
		set_interrupt_id(cpu, INTERRUPT_INVALID_REGISTER_ID);
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
		/* If the registerID is incorrect for
		 * this instruction then raise an
		 * interrupt.
		 */
		interrupt(cpu);
		
		/* Set the interrupt id */
		set_interrupt_id(cpu, INTERRUPT_INVALID_REGISTER_ID);	
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
 * The registerID register holds the interrupt
 * id.
 */
void interrupt(struct CPU* cpu)
{
	/* Set the interrupt bit in the flags register */
	cpu->registerFile.flags = cpu->registerFile.flags | 2;

	/* Get the registerID */
	char registerID = get_registerID(cpu->registerFile.instruction);

	/* Mmmh won;t we have an infite vector looop wait no,as we set it in that case */

	/* Make sure the registerID is that of a byte register */
	if (is_byte_register(registerID)) {
		/* Get the value at the register given and save it as the register */
	} else {
		/* TODO: Raise exception interrupt here */
		/* We must set an internal register that mdifies instruction of interrupt to a register
		 * with our value, fuck me how nigga */
	}

	/* get the interrupt id */
	//char interrupt_id = cpu->registerFile.a
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