/* TODO:
 *
 * - Make method for getting register type []
 * - Register copy methods []
 *
 */

/* The type of register (TODO: (done) optimized to integer) */
enum registerType
{
	BYTE_REGISTER,
	SHORT_REGISTER,
	LONG_REGISTER,

	UNKNOWN_REGISTER_TYPE
};

/* Function for returning funciton piinter to copying function dependant on type */

/* Byte-to-byte register copy */
void byte_to_byte_register_copy(struct CPU* cpu, unsigned char registerID_source, unsigned char registerID_destination)
{
	/* TODO: Type checking, but be loose if not needed (sure about add and subtract are same) */

	/* The byte-wide registers base */
	char* bwrBase = &(cpu->registerFile.a);

	/* Source register */
	char* sourceRegister = bwrBase+registerID_source;
	
	/* Destination register */
	char* destinationRegister = bwrBase+registerID_destination;

	/* Copy the value from the source register into the
	 * destination register.
	 */
	*destinationRegister = *sourceRegister;
}

/* short/word-to-short/word register copy */
void short_to_short_register_copy(struct CPU* cpu, unsigned char registerID_source, unsigned char registerID_destination)
{
	/* TODO: Implement me */
}

/* long-to-long register copy */
void long_to_long_register_copy(struct CPU* cpu, unsigned char registerID_source, unsigned char registerID_destination)
{
	/* TODO: Implement me */
}

/* Checks whether the registerID is a byte register */
char is_byte_register(unsigned char registerID)
{
	return (registerID >= 0 && registerID <= 7);
}

/* Checks whether the registerID is a short/word register */
char is_word_register(unsigned char registerID)
{
	return (registerID >= 8 && registerID <= 15);
}

/* Checks whether the registerID is a double-word register */
char is_double_word_register(unsigned char registerID)
{
	return (registerID >= 16 && registerID <= 23);
}

/* TODO: Add register value fetch function */


/* /\_/\ */
enum registerType get_register_type(char registerID)
{
	/* TODO: Add comment */
	if (is_byte_register(registerID)) {
		/* */
		return BYTE_REGISTER;
	}  else if (is_word_register(registerID)) {
		/* */
		return SHORT_REGISTER;
	} else if (is_double_word_register(registerID)) {
		/* */
		return LONG_REGISTER;
	} else {
		/* */
		return UNKNOWN_REGISTER_TYPE;
	}
}

void* get_copy_function (enum registerType register_type)
{
	/* TODO: Function pointer */

	/* Pointer to the `copy` function */
	void (*copy_function_pointer) (struct CPU*, char, char);

	/* Determine which `copy` function to use based on the register_type */
	if (register_type == BYTE_REGISTER) {
		/* Set the copy function pointer for byte registers */
		copy_function_pointer = byte_to_byte_register_copy;
	} else if (register_type == SHORT_REGISTER) {
		/* Set the copy function pointer for short registers */
		copy_function_pointer = short_to_short_register_copy;
	} else {
		/* Set the copy function pointer for long registers */
		copy_function_pointer = long_to_long_register_copy;
	}

	return copy_function_pointer;
}

/* Get the registerID of a supporting instruction */
char get_registerID(int instruction)
{
	char registerID = *(((char*)&instruction)+1);
	return registerID;
}

/* Get the registerID of a supporting instruction (second register) */
char get_registerID_secondary(int instruction)
{
	char registerID = *(((char*)&instruction)+2);
	return registerID;
}