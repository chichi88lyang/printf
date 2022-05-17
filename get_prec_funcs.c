#include "main.h"
#include <stdlib.h>
char *do_digit_precision(char *str, int prec, int len);
/**
 * do_precision - Perform precision on integer and strings. For integers,
 * controls minimum number of digits to print, pad with 0s if needed. For
 * strings, controls maximum number of characters to print.
 * @str: Pointer to string.
 * @prec: Precision value.
 * @spec: Charater specifier. eg. s for strings, d for integers.
 *
 * Return: Pointer to the new string.
 */

char *do_precision(char *str, int prec, char spec)
{
	char *ret;
	int len, i;
	char int_array[] = {'i', 'd', 'o', 'u', 'x', 'X', 'p', 0};

	ret = str;
	len = _strlen(str);
	if (ch_in_array(spec, int_array))
	{
		return (do_digit_precision(str, prec, len));
	}
	else if (spec == 's')
	{
		if (len > prec)
		{
			ret = malloc(prec + 1);
			for (i = 0; i < prec; i++)
				ret[i] = str[i];
			ret[i] = '\0';
			free(str);
		}
		else
			return (str);
	}
	return (ret);
}
/**
 * do_digit_precision - helper function for do_precision, performed on digits
 * @str: pointer to string in memory that we need to do precision on
 * @prec: integer representing precision needed/specified
 * @len: length of string, passed from do_precision
 *
 * Return: pointer to new string in memory containing old string, effected
 * by precision accordingly.
 */
char *do_digit_precision(char *str, int prec, int len)
{
	char *ret;
	int i, j;

	if (str[0] == '-')
	{
		if (len > prec)
			return (str);
		ret = malloc(prec + 2);
		if (!ret)
			return (NULL);
		i = prec + 1;
		j = len;
		while (j >= 1)
			ret[i--] = str[j--];
		while (i >= 1)
			ret[i--] = '0';
		ret[0] = '-';
		free(str);
	}
	else if (str[0] == '0' && len == 1)
	{
		if (prec == 0)
		{
			str[0] = '\0';
			return (str);
		}
		ret = do_width(str, prec, 1);
	}
	else
		ret = do_width(str, prec, 1);
	return (ret);
}
