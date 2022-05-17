#include "main.h"
#include <unistd.h>
#include <stdlib.h>
/**
 * create_buff - creates a buffer in memory and sets to 0
 * @bytes: number of bytes to allocate for buffer
 *
 * Return: char pointer to beginning of buffer
 */
char *create_buff(unsigned int bytes)
{
	char *new_buff;

	new_buff = malloc(bytes);
	if (!new_buff)
		return (NULL);
	/*for (i = 0; i < bytes; i++)*/
	/*	new_buff[i] = 0; */
	return (new_buff);
}
/**
 * copy_buff - copies a string into the buffer
 * @str: string to copy into buffer
 * @help_s: pointer to printh_t struct containing buffer, buff_i, etc..
 *
 * Return: number of bytes written
 */
unsigned int copy_buff(char *str, printh_t *help_s)
{
	unsigned int i = 0;

	if (!str || !help_s->buff)
		return (0);
	while (str[i] && help_s->buff_i < BUFF_SIZE)
	{
		help_s->buff[help_s->buff_i] = str[i];
		help_s->buff_i++, i++;
		if (help_s->buff_i == BUFF_SIZE)
		{
			print_buff(help_s->buff, BUFF_SIZE);
			free(help_s->buff);
			help_s->buff = create_buff(BUFF_SIZE);
			if (!help_s->buff)
				return (i);
			help_s->buff_i = 0;
		}
	}
	if (help_s->c != str) /* addresses */
		free(str);
	return (i);
}
/**
 * print_buff - prints the contents of the buffer
 * @buff: buffer to print
 * @buff_size: size of buffer in bytes
 *
 * Return: number of bytes written
 */
unsigned int print_buff(char *buff, unsigned int buff_size)
{
	unsigned int bytes_written;

	bytes_written = write(1, buff, buff_size);
	return (bytes_written);
}

/**
 * free_all - Frees all memory in structure and args.
 * @help_s: The pointer to a malloced structure.
 * @args: Pointer to a va_list.
 *
 * Return: Void.
 */
void free_all(printh_t *help_s, va_list args)
{
	if (help_s)
	{
		if (help_s->flags)
			free(help_s->flags);
		if (help_s->buff)
			free(help_s->buff);
		if (help_s->c)
			free(help_s->c);
		if (help_s->mods)
			free(help_s->mods);
		free(help_s);
	}
	va_end(args);
}
