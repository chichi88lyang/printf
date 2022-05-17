/**
 * _isdigit - checks if a character is a digit or not
 * @c: character to check
 *
 * Return: 1 if isdigit, 0 if not digit
 */
int _isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * is_modifier - checks if a character is a length modifier
 * @c: character to check
 *
 * Return: 1 if modifier, otherwise 0.
 */
int is_modifier(char c)
{
	if (c == 'l' || c == 'h')
		return (1);
	return (0);
}
/**
 * _abs - gets absolute value of integer
 * @n: integer to get absolute value for
 *
 * Return: unsigned int containing abs
 */
unsigned int _abs(int n)
{
	return ((n < 0) ? -(unsigned int)n : (unsigned int)n);
}