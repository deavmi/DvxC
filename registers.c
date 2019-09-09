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