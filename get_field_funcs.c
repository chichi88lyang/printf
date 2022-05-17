#include "main.h"
#include <stdlib.h>
/**
 * get_width_precision - gets the width and precision for a format string
 * @help_s: pointer to our helper struct to contain variables for passing
 * @args: va_list of args to advance and use
 *
 * Return: always void
 */

void get_width_precision(printh_t *help_s, va_list args)
{
	char c;
	char dot;

	c = help_s->format[help_s->f_i];
	dot = help_s->dot;

	if (c == '.')
		help_s->dot = 1;
	else if (_isdigit(c))
	{
		c -= '0';
		if (!dot)
			help_s->width = (c + (help_s->width * 10));
		else
			help_s->precision = (c + (help_s->precision * 10));
	}
	else if (c == '*')
	{
		if (!dot)
			help_s->width = va_arg(args, int);
		else
			help_s->precision = va_arg(args, int);
	}
}

/**
 * do_width - Applies spaces or '0's in front of strings if their length is
 * less than the specified minimum width.
 * @str: The string to modify.
 * @width: The minimum width the string should have.
 * @zero: if 1, pad with 0's, otherwise pad with space.
 *
 * Return: char pointer to the new string.
 */

char *do_width(char *str, int width, int zero)
{
	int len, i, j, stop;
	char *ret;
	char pad, sign;

	stop = 0;
	len = _strlen(str);
	if (len > width)
		return (str);
	ret = malloc(width + 1);
	if (!ret)
		return (NULL);
	if (zero)
	{
		pad = '0';
		sign = str[0];
		if (str[0] == '+' || str[0] == '-' || str[0] == ' ')
		{
			ret[0] = sign;
			stop = 1;
		}
		if (str[0] == '0' && str[1] == 'x')
		{
			ret[0] = '0';
			ret[1] = 'x';
			stop = 2;
		}
	}
	else
	{
		pad = ' ';
	}
	i = width;
	j = len;
	while (j >= stop)
		ret[i--] = str[j--];

	while (i >= stop)
		ret[i--] = pad;
	free(str);
	return (ret);
}

/**
 * do_shift - Takes a string and if its' length is less than width, add n
 * spaces after the string, where n is the difference between length and width.
 * @str: Pointer to the passed string.
 * @width: Minimum number of characters to be printed. if len < width, pad
 * the end of the string with spaces using the difference.
 *
 * Return: The left justified string.
 */
char *do_shift(char *str, int width)
{
	int len, i;
	char *ret;

	len = _strlen(str);
	if (len > width)
		return (str);
	ret = malloc(width + 1);
	if (!ret)
		return (NULL);
	for (i = 0; str[i]; i++)
		ret[i] = str[i];
	for (; i < width; i++)
		ret[i] = ' ';
	ret[i] = '\0';
	free(str);
	return (ret);
}
