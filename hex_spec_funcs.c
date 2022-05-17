#include "main.h"
#include <stdlib.h>

/**
 * get_hex - gets a string that is the hex representation of an integer
 * @args: va_list to get integer for conversion from
 * @mods: array containing length modifier bytes, representing t/f for l & h
 *
 * Return: char pointer to new hex string
 */
char *get_hex(va_list args, char *mods)
{
	int num_i;
	unsigned int num;
	unsigned long int num_l;
	char *ret;

	if (mods[0] > 0 && mods[1] == 0) /* l byte is lit, h is not */
	{
		num_l = va_arg(args, unsigned long int);
		ret = get_hex_long_n(num_l);
	}
	else if (mods[1] > 0 && mods[0] == 0) /* h byte lit, l is not */
	{
		num_i = va_arg(args, int);
		num = _abs(num_i);
		ret = get_hex_n(num);
	}
	else /* both are lit (cancels out), or no length mods are lit */
	{
		num = va_arg(args, unsigned int);
		ret = get_hex_n(num);
	}
	return (ret);
}
/**
 * get_hex_upper - gets a string that is the upper case hex rep of an integer
 * @args: va_list to get integer for conversion from
 * @mods: array containing length modifier bytes, representing t/f for l & h
 *
 * Return: char pointer to new hex string
 */
char *get_hex_upper(va_list args, char *mods)
{
	char *ret;

	ret = get_hex(args, mods);
	_string_upper(ret);

	return (ret);
}
/**
 * get_pointer - gets a string that contains an address in hexadecimals.
 * @args: va_list to get hexadecimal from.
 * @mods: length modifiers, voided, not used with this specifier
 *
 * Return: char pointer to the string. NULL if malloc fails.
 */
char *get_pointer(va_list args, char *mods)
{
	int length, i;
	unsigned long int addr, temp, rem;
	char *ret;

	(void)mods;
	addr = va_arg(args, unsigned long int);
	length = 1;
	temp = addr;
	if (addr == 0)
	{
		ret = malloc(5 + 1);
		ret = _strcpy(ret, "(nil)");
		return (ret);
	}
	while (temp > 15)
	{
		temp /= 16;
		length++;
	}

	ret = malloc(length + 1);
	if (!ret)
		return (NULL);
	ret[length] = '\0';
	i = length - 1;
	while (i >= 0)
	{
		rem = addr % 16;
		if (rem > 9)
			ret[i] = rem + 87;
		else
			ret[i] = rem + '0';
		addr /= 16;
		i--;
	}
	return (ret);
}
