#include "main.h"
#include <stdlib.h>

/**
 * get_reverse - Get the reversed copy of the string.
 * @args: va_list containing the string.
 * @mods: length modifiers, voided, not used with this specifier
 *
 * Return: char pointer to the reversed string.
 */

char *get_reverse(va_list args, char *mods)
{
	int i;
	int length;
	char *str, *ret;

	(void)mods;
	str = va_arg(args, char *);
	length = _strlen(str);
	ret = malloc(length + 1);
	if (!ret)
		return (NULL);

	for (i = 0; i < length; i++)
		ret[i] = str[length - i - 1];
	ret[i] = '\0';

	return (ret);
}

/**
 * get_rot - Gets the Rot13'd copy of the string
 * @args: va_list containing the string
 * @mods: length modifiers, voided, not used with this specifier
 *
 * Return: char pointer to newly allocated and rot13'd string
 */

char *get_rot(va_list args, char *mods)
{
	int index, length;
	unsigned char temp_c;
	char is_upper;
	char *str, *ret;

	(void)mods;
	str = va_arg(args, char *);
	length = _strlen(str);
	ret = malloc(length + 1);
	if (!ret)
		return (NULL);
	index = 0;
	while (str[index])
	{
		temp_c = (unsigned char)str[index];
		if (_isalpha(temp_c))
		{
			is_upper = (temp_c >= 'A' && temp_c <= 'Z');
			temp_c += 13;
			if (is_upper)
			{
				if (temp_c > 'Z')
					temp_c -= 26;
			}
			else
			{
				if (temp_c > 'z')
					temp_c -= 26;
			}
		}
		ret[index] = (char)temp_c;
		index++;
	}
	ret[length] = '\0';
	return (ret);
}

/**
 * get_nonprint_string - gets a pointer to a string in memory containing np's
 * @args: va_list to get string containing non printables
 * @mods: length modifiers, voided, not used with this specifier
 *
 * Return: pointer to newly allocated string containing hex's for np's
 */

char *get_nonprint_string(va_list args, char *mods)
{
	char *str, *ret;
	int length, i;

	(void)mods;
	str = va_arg(args, char *);
	length = 0;
	i = 0;

	while (str[i])
	{
		if (!is_printable(str[i]))
		{
			length += 4;
		}
		else
			length++;
		i++;

	}
	i = 0;
	ret = malloc(length + 1);
	if (!ret)
		return (NULL);
	if (!fill_nonprint_buffer(length, ret, str))
	{
		free(ret);
		return (NULL);
	}

	return (ret);
}

/**
 * get_binary - convert unsigned integer to binary representation.
 * @args: va_list containing the unsigned integer.
 * @mods: length modifiers, voided, not used with this specifier
 *
 * Return: char pointer to the binary string. NULL if malloc fails.
 */

char *get_binary(va_list args, char *mods)
{
	unsigned int num;
	int length;
	char *ret;

	(void)mods;
	num = va_arg(args, unsigned int);
	length = get_numbase_len(num, 2);

	ret = malloc(length + 1);
	if (!ret)
		return (NULL);

	fill_numbase_buff(num, 2, ret, length);

	return (ret);
}
