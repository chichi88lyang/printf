#include "main.h"
#define NULL 0
/**
 * get_string_func - gets a pointer to a function
 * @ch: char to match with specifier function
 *
 * Return: pointer to a function that takes va_list and returns char *
 */
char *(*get_string_func(char ch))(va_list, char *mods)
{
	spec_t specs[] = {
		{ 'c', get_char },
		{ 's', get_string },
		{ 'S', get_nonprint_string },
		{ '%', get_percent },
		{ 'd', get_int },
		{ 'i', get_int },
		{ 'b', get_binary },
		{ 'u', get_unsigned },
		{ 'o', get_octal },
		{ 'x', get_hex },
		{ 'X', get_hex_upper },
		{ 'p', get_pointer },
		{ 'r', get_reverse },
		{ 'R', get_rot },
		{ NULL, NULL }
	};
	int i = 0;

	while (specs[i].t != ch)
		i++;
	return (specs[i].f);
}
