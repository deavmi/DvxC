/* CPU */

#include "memory/memory.h"

struct RegisterFile
{
	/* 8-bit registers */
	char a;
	char b;
	char c;
	char d;
	char e;
	char f;
	char g;
	char h;
	
	/* 16-bit registers */
	short ae;
	short be;
	short ce;
	short de;
	short ee;
	short fe;
	short ge;
	short he;

	/* 32-bit registers */
	int aex;
	int bex;
	int cex;
	int dex;
	int eex;
	int fex;
	int gex;
	int hex;

	/* Special purpose registers
	 *
	 * All of these registers have special meaning
	 * to the machine by their values, or, to the user
	 * as a way to signal the program information.
	 */

	/* The current instruction address */
	unsigned int ip;

	/* Flags register
	 *
	 * This register holds information that a lot
	 * of instructions might set status bits for
	 * for certain errors etc.
	 */
	int flags;

	/* Vector table
	 *
	 * Address of the table of exception handlers
	 * (vector table).
	 */
	int vector_table;

	/* Interrupt register */
	char interrupt_register;

	/* The currently executing instruction */
	int instruction;

};

struct CPU
{
	/* Register file */
	struct RegisterFile registerFile;

	/* Memory module */
	struct Memory memoryModule;

	/* Whether or not the CPU is active */
	char is_active;

};