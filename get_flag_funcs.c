#include "main.h"
#include <stdlib.h>

/**
 * get_flag_func - gets the proper function for a flag
 * @flag_index: index of flag gotten from _isflag, consistent with struct arr
 * @spec: specifier to make sure flag supports it
 *
 * Return: pointer to a function that takes a char * and returns a char *
 */
char *(*get_flag_func(int flag_index, char spec))(char *)
{
	char only_ints[] = {'d', 'i', 'p', '\0' };
	char only_hex[] = {'o', 'x', 'X', '\0' };
	char all[] = { 'o', 'x', 'X', 'd', 'i', 'p', '\0' };
	flag_t flags[6];

	flags[0].flag = '+';
	flags[0].specs = only_ints;
	flags[0].f = do_plus_flag;
	flags[1].flag = ' ';
	flags[1].specs = only_ints;
	flags[1].f = do_spc_flag;
	flags[2].flag = '#';
	flags[2].specs = only_hex;
	flags[2].f = NULL;
	flags[3].flag = '-';
	flags[3].specs = all;
	flags[3].f = NULL;
	flags[4].flag = '0';
	flags[4].specs = all;
	flags[4].f = NULL;
	flags[5].flag = 0;
	flags[5].specs = NULL;
	flags[5].f = NULL;
	switch (spec)
	{
		case ('o'):
			flags[2].f = do_octal_flag;
			break;
		case ('x'):
			flags[2].f = do_hex_flag;
			break;
		case ('X'):
			flags[2].f = do_hex_upper_flag;
			break;
		default:
			break;
	}
	if (ch_in_array(spec, flags[flag_index].specs))
		return (flags[flag_index].f);
	return (NULL);
}

/**
 * perform_flag_funcs - Perform flag functions that were encountered on the
 * string.
 * @flags: An array int to keep track of which flags were encountered. 1 if
 * encountered, otherwise 0.
 * @temp: The string to perform functions on.
 * @spec: The specifier.
 *
 * Return: char pointer to the formatted string.
 */

char *perform_flag_funcs(int *flags, char *temp, char spec)
{
	int i;
	char *(*f)(char *);

	for (i = 0; i < 5; i++)
	{
		if (flags[i])
		{
			f = get_flag_func(i, spec);
			if (f)
				temp = f(temp);
			if (!temp)
				return (NULL);
		}
	}
	return (temp);
}
