#include "main.h"
#include <stdlib.h>
char *perform_sub_specs(char *temp, printh_t *help_s);
/**
 * handle_alpha_percent - Handle cases for alpha characters that are valid
 * specs, modifiers, invalid specs.
 * @help_s: Pointer to struct containing specifier information.
 * @args: Pointer to va_list.
 * Return: 1 for success, 0 for failure.
 */

int handle_alpha_percent(printh_t *help_s, va_list args)
{
	char *temp;
	int mod_index;

	mod_index = is_modifier(help_s->format[help_s->f_i]);
	if (is_specifier(help_s->format[help_s->f_i]))
	{
		temp = get_string_func(help_s->format[help_s->f_i])(args, help_s->mods);
		if (!temp)
			return (0);
		if (temp[0] == '\0' && help_s->format[help_s->f_i] == 'c')
		{
			insert_null_char(help_s);
			exit_busy_reset(help_s, 1);
			free(temp);
			return (1);
		}
		else
			temp = perform_sub_specs(temp, help_s);
		if (!temp)
			return (0);
		help_s->buff_len += copy_buff(temp, help_s);

		exit_busy_reset(help_s, 1);
	}
	else if (mod_index)
	{
		if (help_s->format[help_s->f_i] == 'l')
			help_s->mods[0] = mod_index;
		else if (help_s->format[help_s->f_i] == 'h')
			help_s->mods[1] = mod_index;
	}
	else
	{
		if (help_s->mods[0] || help_s->mods[1])
			(help_s->spec_c)++;
		help_s->f_i = help_s->beg_i;
		help_s->buff[(help_s->buff_i)++] = help_s->format[help_s->f_i];
		help_s->buff_len++;
		exit_busy_reset(help_s, 0);
	}
	return (1);
}
/**
 * perform_sub_specs - Performs sub specifier formats on the specifier string.
 * @temp: Pointer to string of the specifier.
 * @help_s: Pointer to structure containing information on all the flags seen
 * between the % and the specifier.
 *
 * Longer description: Performs precision on the string if precision was seen.
 * Next if the specifier is a pointer and the string does not contain '(' from
 * (nil) (for null pointers) append 0x to the string. Afterwards, ' ', '+', '0'
 * , '0x', '0X' is appended for applicable integer values if the flags ' ', '+'
 * ,'#' was set. Left justified is performed on the string next if '-' flag was
 * specified with a value. If left justified is performd, width that is
 * performed next will not occur.Lastly width, padding with either zeroes or
 * spaces is applied if the flags was set. Width with padding for zeroes will
 * not occur is precision was performed; if a width was specified with
 * precision, the string will be padded with spaces.
 *
 * Return: A formatted specifier string.
 */
char *perform_sub_specs(char *temp, printh_t *help_s)
{
	char current_spec;
	int precision, width, dot_flag, shift_flag, zero_flag;

	current_spec = help_s->format[help_s->f_i];
	precision = help_s->precision;
	width = help_s->width;
	dot_flag = help_s->dot;
	shift_flag = help_s->flags[3];
	zero_flag = help_s->flags[4];

	if (dot_flag)
	{
		temp = do_precision(temp, precision, current_spec);
		zero_flag = 0;
	}
	if (current_spec == 'p' && temp[0] != '(')
		/* append 0x to pointer if it is not (nil) */
		temp = do_hex_flag(temp);
	temp = perform_flag_funcs(help_s->flags, temp, current_spec);
	if (shift_flag)
	{
		temp = do_shift(temp, width);
		zero_flag = 0;
		width = 0;
	}
	if (zero_flag && current_spec != 's' && current_spec != 'c')
		temp = do_width(temp, width, 1);
	else
		temp = do_width(temp, width, 0);
	return (temp);
}
