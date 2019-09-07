#include "memory.c"

void initialize_memory_module(struct CPU* cpu)
{
	initialize_memory(cpu, 2);
}

/* TODO: Pointers cast to unsigned int should be unsigned long) */

void initialize_registers(struct CPU* cpu)
{
	printf("Initializing registers...\n");

	/* Base address of byte-wide registers */
	char* bwrBase = &(cpu->registerFile.a);
	printf("Base address of 1-byte registers: %u\n", (unsigned int)bwrBase);

	/* Initialize the 8 byte-wide registers */
	for (unsigned char i = 0; i < 8; i++) {
		/* The current register */
		char* bwrCurrent = bwrBase+i;
		printf("Current address of 1-byte register: %d\n", (unsigned int)bwrCurrent);
		
		*(bwrCurrent) = 0;
	}

	/* Base address of short/word-wide registers */
	short* swrBase = &(cpu->registerFile.ae);
	printf("Base address of 2-byte registers: %u\n", (unsigned int)swrBase);

	/* Initialize the 8 short/word-wide registers */
	for (unsigned char i = 0; i < 8; i++) {
		/* The current register */
		short* swrCurrent = swrBase+i;
		printf("Current address of 2-byte register: %d\n", (unsigned int)swrCurrent);
		
		*(swrCurrent) = 0;
	}

	/* Base address of double-word-wide registers */
	int* dwwrBase = &(cpu->registerFile.aex);
	printf("Base address of 4-byte registers: %u\n", (unsigned int)swrBase);

	/* Initialize the 8 double-word-wide registers */
	for (unsigned char i = 0; i < 8; i++) {
		/* The current register */
		int* dwwrCurrent = dwwrBase+i;
		printf("Current address of 4-byte register: %d\n", (unsigned int)dwwrCurrent);
	
		*(dwwrCurrent) = 0;
	}

	printf("Registers initialized\n");
}

void initialize_cpu(struct CPU* cpu)
{
	/* Initialize all the registers */
	initialize_registers(cpu);

	/* Initialize the Memory module */
	initialize_memory_module(cpu);

	/* Set the CPU to active */
	cpu->is_active = 1;
}

struct CPU* new_cpu()
{
	/* Allocate space for the CPU struct on the heap */
	struct CPU* cpu = malloc(sizeof(struct CPU));

	/* Initialize the CPU */
	initialize_cpu(cpu);

	return cpu;
}





int get_instruction(struct CPU* cpu)
{
	/* The fetched instruction */
	int instruction;
	
	/* Address to the current instruction to be fetched */
	int ip = cpu->registerFile.ip;
	printf("Fetching instruction at %u\n", ip);

	/* TODO: Add instruction fetch here */

	return instruction;
}


/* Returns 1 if we are in real mode, 0 if protected */
char is_real_mode(struct CPU* cpu)
{
	/* TODO: Implement me */
	char is_real_mode_result = 1;
	
	return is_real_mode_result;
}

char process_instruction(struct CPU* cpu)
{
	/* Whether or not we increment ip after processing
	 * this instruction.
	 */
	char increment_ip = 0;
	
	/* Store instruction locally (clearer code) */
	int instruction = cpu->registerFile.instruction;
	printf("Current instruction: %u\n", instruction);
	
	/* Get the OP code */
	char op_code = *((char*)&instruction);
	printf("Operation code: %u\n", op_code);

	/* Check the OP code now and determine what
	 * instruction needs to be executed.
	 */
	if (op_code == 0) {
		/* Nop instruction
		 *
		 * Do nothing
		 */
		 nop();
	} else if (op_code == 1) {
		/* This op code is for that very special person */
		/* TODO: huisdans */
	} else if (op_code == 2) {
		/* Move byte immediate to register instruction
		 *
		 * Moves the lower immediate byte into
		 * the given register.
		 */
		 register_assign_byte(cpu);
	} else if (op_code == 3) {
		/* Move short immediate to register instruction
		 *
		 * Moves the short immediate into
		 * the given register.
		 */
		 register_assign_short(cpu);
	} else if (op_code == 4) {
		/* Move short immediate to upper of register instruction
		 *
		 * Moves the short immediate into
		 * the given register's upper 16-bits.
		 */
		 register_assign_upper(cpu);
	} else if (op_code == 9) {
		/* Raises an interrupt
		 *
		 * Raises an interrupt with the
		 * given ID in the register provided.
		 */
		 interrupt(cpu);
	} else if (op_code == 10) {
		/* Returns from a interrupt
		 *
		 * Sets `ip` to the value stored in
		 * the `hex` register.
		 */
		interrupt_return(cpu);
	} else if (op_code == 11) {
		/* Halt the CPU */
		halt(cpu);
	}

	return increment_ip;
}

void cpu(struct CPU* cpu)
{
	/* State machine loop */
	while (cpu->is_active) {
		/* Get the current instruction */
		get_instruction(cpu);
		printf("Instruction: %u\n", cpu->registerFile.instruction);

		/* Process the instruction */
		char must_increment_ip = process_instruction(cpu);
		printf("msut_increment_ip: %u\n", must_increment_ip);

		/* Check the interrupt register */
		int interrupt_status = cpu->registerFile.flags; /* TODO: Mask the bit */
		printf("Interrupt status: %u\n", interrupt_status);
		if (interrupt_status) {
			/* Handle the interrupt */
			interrupt(cpu);
		} else {
			/* If not handling an interrupt */

			/* Check if the `ip` register should be incremented by 4 bytes */
			if (must_increment_ip) {
				/* TODO: Implement */
				/* Increment the instruction pointer by 4 bytes */
				cpu->registerFile.ip += 4;
			} else {
				/* TODO: Implement */
			}
		}
	}
}


#include "instructions/instructions.c"