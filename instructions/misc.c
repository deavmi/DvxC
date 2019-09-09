/* Set the `h` register */
void set_interrupt_id(struct CPU* cpu, char interrupt_id)
{
	/* Set the `h` register to the interrupt id given */
	cpu->registerFile.h = interrupt_id;
}