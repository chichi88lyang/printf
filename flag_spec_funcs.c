#include "main.h"
#include <stdlib.h>

/**
 * do_plus_flag - Add a '+' in front of positive integers.
 * @str: The string containing the integer. Assume not NULL.
 *
 * Return: Void.
 */

char *do_plus_flag(char *str)
{
	int i, length;
	char *ret;

	if (str[0] == '-')
		return (str);

	length = _strlen(str);
	i = 0;
	ret = malloc(1 + length + 1);
	ret[i++] = '+';
	for (; i < length + 1; i++)
		ret[i] = str[i - 1];
	ret[i] = '\0';
	free(str);
	return (ret);
}

/**
 * do_spc_flag - Insert space in front of positive integers.
 * @str: The string containing the integer. Assume not NULL.
 *
 * Return: The char pointer with space in front of integer value. Returns str
 * if integer is negative or has a '+' in front already.
 */

char *do_spc_flag(char *str)
{
	int i, length;
	char *ret;

	if (str[0] == '-' || str[0] == '+')
		return (str);

	length = _strlen(str);
	i = 0;
	ret = malloc(1 + length + 1);
	ret[i++] = ' ';
	for (; i < length + 1; i++)
		ret[i] = str[i - 1];
	ret[i] = '\0';
	free(str);
	return (ret);
}

/**
 * do_octal_flag - Insert 0 in front of non 0 octal.
 * @str: The string containing the octal. Assume not NULL.
 *
 * Return: The char pointer with 0 in front of octal value. Returns str if
 * octal value is 0.
 */

char *do_octal_flag(char *str)
{
	int i, length;
	char *ret;

	length = _strlen(str);
	if (str[0] == '0' && length == 1)
		return (str);

	i = 0;
	ret = malloc(1 + length + 1);
	ret[i++] = '0';
	for (; i < length + 1; i++)
		ret[i] = str[i - 1];
	ret[i] = '\0';
	free(str);

	return (ret);
}

/**
 * do_hex_flag - Insert 0x in front of non 0 hex value.
 * @str: The string containing the hexadecimal. Assume not NULL.
 *
 * Return: The char pointer with 0x in front of hex value. Returns str if hex
 * value is 0.
 */

char *do_hex_flag(char *str)
{
	int i, length;
	char *ret;

	length = _strlen(str);
	if (str[0] == '0' && length == 1)
		return (str);

	i = 0;
	ret = malloc(2 + length + 1);
	ret[i++] = '0';
	ret[i++] = 'x';
	for (; i < length + 2; i++)
		ret[i] = str[i - 2];
	ret[i] = '\0';
	free(str);

	return (ret);
}

/**
 * do_hex_upper_flag - Insert 0X in front of non 0 hex value.
 * @str: The string containing the hexadecimal. Assume not NULL.
 *
 * Return: The char pointer with 0X in front of hex value. Returns str if hex
 * value is 0.
 */

char *do_hex_upper_flag(char *str)
{
	char *ret;

	ret = do_hex_flag(str);
	if (ret[1] == 'x')
		ret[1] = 'X';

	return (ret);
}
