#include <stdlib.h>
#include "main.h"

/**
 * _strlen - gets length of string, not including null byte
 * @str: string to get length of
 *
 * Return: length of string
 */
int _strlen(char *str)
{
	int i = 0;

	while (*(str + i))
		i++;
	return (i);
}
/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * _string_upper - Converts lowercase characters in a string to uppercase.
 * @str: char pointer to the string.
 *
 * Return: Void.
 */
void _string_upper(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
}
/**
 * fill_nonprint_buffer - fills a buffer with given string, replacing nonprints
 * @length: length of buffer in bytes
 * @buff: char pointer to buffer in memory
 * @str: char pointer to string to copy into buffer in memory
 *
 * Return: 1 on success, 0 on malloc failure of hexvalue for nonprints
 */
int fill_nonprint_buffer(int length, char *buff, char *str)
{
	int i, j;
	char *hex_val;

	i = 0, j = 0;
	while (i < length)
	{
		if (!is_printable(str[j]) && str[j] > 0)
		{
			hex_val = get_hex_n((unsigned int)str[j]);
			if (!hex_val)
				return (0);
			buff[i++] = '\\';
			buff[i++] = 'x';
			_string_upper(hex_val);
			if (hex_val[1])
			{
				buff[i++] = hex_val[0];
				buff[i++] = hex_val[1];
			}
			else
			{
				buff[i++] = '0';
				buff[i++] = hex_val[0];
			}
			free(hex_val);
		}
		else
		{
			buff[i] = str[j];
			i++;
		}
		j++;
	}
	buff[length] = '\0';
	return (1);
}
