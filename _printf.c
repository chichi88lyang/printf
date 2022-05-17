#include "main.h"
#include <stdlib.h>
int print_helper(printh_t *help_s, va_list args);
printh_t *init_help_s(const char *, va_list args);
/**
  * _printf - Prints variatic arguments based on format string.
  * @format: String passed, may contain zero, or more directives.
  *
  * Return: Number of characters printed to stdout.
  */

int _printf(const char *format, ...)
{
	int E;
	unsigned int t_bytes;
	va_list args;
	printh_t *help_s;

	if (!format)
		return (-1);
	va_start(args, format);
	help_s = init_help_s(format, args);
	if (!help_s)
		return (-1);
	E = 0;

	while (format[help_s->f_i])
	{
		if (format[help_s->f_i] == '%' && !help_s->busy)
		{
			help_s->beg_i = help_s->f_i;
			help_s->busy = 1;
			if (format[help_s->f_i + 1] == '\0')
			{
				if (help_s->spec_c)
				{
					help_s->buff[help_s->buff_i++] = format[help_s->f_i];
					help_s->buff_len++;
					exit_busy_reset(help_s, 1);
				}
				else
				{
					free_all(help_s, args);
					return (-1);
				}
			}
		}
		else if (help_s->busy)
		{
			E = print_helper(help_s, args);
			if (!E)
			{
				free_all(help_s, args);
				return (-1);
			}
		}
		else if (!(format[help_s->f_i] == 'l' && help_s->mods[0])
				&& !(format[help_s->f_i] == 'h' && help_s->mods[1]))
		{
			help_s->c[0] = format[help_s->f_i];
			help_s->c[1] = '\0';
			help_s->buff_len += copy_buff(help_s->c, help_s);
		}
		else
		{
			help_s->mods[0] = 0;
			help_s->mods[1] = 0;
		}
		help_s->f_i++;
	}
	if (help_s->busy && format[help_s->f_i] == '\0')
	{
		print_buff(help_s->buff, help_s->beg_i - 1);
		free_all(help_s, args);
		return (-1);
	}
	print_buff(help_s->buff, help_s->buff_i);
	t_bytes = help_s->buff_len;
	free_all(help_s, args);
	return (t_bytes);
}
/**
 * print_helper - print helper function to split up logic of _printf
 * @help_s: pointer to our helper struct to contain variables for passing
 * @args: va_list of args to advance and use
 *
 * Return: 1 on success, 0 on failure
 */
int print_helper(printh_t *help_s, va_list args)
{
	int flag_index, mod_index;

	flag_index = is_flag(help_s->format[help_s->f_i],
			help_s->format[help_s->f_i - 1]);
	mod_index = is_modifier(help_s->format[help_s->f_i]);
	if (flag_index > -1)
		help_s->flags[flag_index] = 1;
	else if (!mod_index)
		(help_s->spec_c)++;
	if (_isalpha(help_s->format[help_s->f_i])
		|| help_s->format[help_s->f_i] == '%')
	{
		return (handle_alpha_percent(help_s, args));
	}
	else if (_isdigit(help_s->format[help_s->f_i]) ||
			help_s->format[help_s->f_i] == '.' ||
			help_s->format[help_s->f_i] == '*')
		get_width_precision(help_s, args);
	else if (help_s->format[(help_s->f_i) + 1] == '\0')
	{
		if (help_s->spec_c)
		{
			help_s->f_i = help_s->beg_i;
			help_s->buff[(help_s->buff_i)++] = help_s->format[help_s->f_i];
			help_s->buff_len++;
			exit_busy_reset(help_s, 0);
		}
		else
			return (0);
	}
	return (1);
}
/**
 * init_help_s - initializes print helper structure, creating space for it
 * @format: pointer to format specifier string to set as pointer
 * @args: va_list pointer, will be sent to free_all to have memory freed if a
 * malloc fails.
 *
 * Return: pointer to structure created in memory
 */
printh_t *init_help_s(const char *format, va_list args)
{
	printh_t *help_s;

	help_s = malloc(sizeof(*help_s));
	if (!help_s)
	{
		va_end(args);
		return (NULL);
	}
	help_s->flags = calloc(5, sizeof(int));
	if (!help_s->flags)
	{
		free_all(help_s, args);
		return (NULL);
	}
	help_s->mods = calloc(2, sizeof(char));
	if (!help_s->mods)
	{
		free_all(help_s, args);
		return (NULL);
	}
	help_s->buff = create_buff(BUFF_SIZE);
	if (!help_s->buff)
	{
		free_all(help_s, args);
		return (NULL);
	}
	help_s->c = create_buff(2);
	if (!help_s->c)
	{
		free_all(help_s, args);
		return (NULL);
	}
	help_s->format = format;
	help_s->dot = help_s->busy = help_s->f_i = help_s->buff_i = 0;
	help_s->beg_i = help_s->buff_len = help_s->width = 0;
	help_s->precision = help_s->spec_c = 0;
	return (help_s);
}


/**
 * exit_busy_reset - Reset values of busy, width, precision, and dot to zero
 * upon exit of busy.
 * @help_s: Pointer to structure.
 * @reset_mods: Flag indicator to reset mods. 1 for reset, 0 do nothing.
 * Return: Void.
 */

void exit_busy_reset(printh_t *help_s, int reset_mods)
{
	int i;

	help_s->busy = 0;
	help_s->width = 0;
	help_s->precision = 0;
	help_s->dot = 0;

	for (i = 0; i < 5; i++)
		help_s->flags[i] = 0;
	if (reset_mods)
	{
		for (i = 0; i < 2; i++)
			help_s->mods[i] = 0;
	}
}
