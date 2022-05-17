#include <stdlib.h>
#include "main.h"

/**
 * get_numbase_len - gets length of buffer needed for an unsigned int
 * @num: number to get length needed for
 * @base: base of number representation used by buffer
 *
 * Return: integer containing length of buffer needed (doesn't contain null bt)
 */
int get_numbase_len(unsigned int num, unsigned int base)
{
	int len = 1; /* all numbers contain atleast one digit */

	while (num > base - 1)
	{
		len++;
		num /= base;
	}
	return (len);
}
/**
 * get_longnumbase_len - gets length of buff needed for long unsigned int
 * @num: number to get length needed for
 * @base: base of number representation that will be used by buffer
 *
 * Return: integer containing length of buffer needed ( no null byte )
 */
int get_longnumbase_len(unsigned long int num, unsigned int base)
{
	int len = 1; /* all numbers contain at least 1 digit */

	while (num > (unsigned long int)base - 1)
	{
		len++;
		num /= (unsigned long int)base;
	}
	return (len);
}
/**
 * fill_numbase_buff - fills buffer with correct numbers up to base 36
 * @num: number to convert to string given base
 * @base: base of number used in conversion, only works up to base 36
 * @buff: buffer to fill with result of conversion
 * @buff_size: size of buffer in bytes
 *
 * Return: always void.
 */
void fill_numbase_buff(unsigned int num, unsigned int base,
			char *buff, int buff_size)
{
	int rem, i = buff_size - 1;

	buff[buff_size] = '\0';
	while (i >= 0)
	{
		rem = num % base;
		if (rem > 9) /* return lowercase ascii val representation */
			buff[i] = rem + 87; /* 10 will be a, 11 = b, ... */
		else
			buff[i] = rem + '0';
		num /= base;
		i--;
	}
}
/**
 * fill_longnumbase_buff - fills buffer with correct numbers up to base 36
 * @num: long int to convert to string of given base
 * @base: base of number used in conversion, only works up to base 36
 * @buff: buffer to fill with result of conversion, not main printf buffer
 * @buff_size: size of buffer in bytes
 *
 * Return: always void.
 */
void fill_longnumbase_buff(unsigned long int num, unsigned int base,
				char *buff, int buff_size)
{
	int rem, i = buff_size - 1;

	buff[buff_size] = '\0';
	while (i >= 0)
	{
		rem = num % (unsigned long int)base;
		if (rem > 9)
			buff[i] = rem + 87;
		else
			buff[i] = rem + '0';
		num /= (unsigned long int)base;
		i--;
	}
}
