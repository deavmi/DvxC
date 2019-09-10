/* TODO:
 *
 * - Make method for getting register type []
 * - Register copy methods []
 *
 */

/* Byte-to-byte register copy */
void byte_to_byte_register_copy(struct CPU* cpu, unsigned char registerID_source, unsigned char registerID_source)
{
	/* TODO: Implement me */
}

/* short/word-to-short/word register copy */
void short_to_short_register_copy(struct CPU* cpu, unsigned char registerID_source, unsigned char registerID_source)
{
	/* TODO: Implement me */
}

/* long-to-long register copy */
void long_to_long_register_copy(struct CPU* cpu, unsigned char registerID_source, unsigned char registerID_source)
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