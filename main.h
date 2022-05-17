#ifndef _PRINTF_H_
#define _PRINTF_H_
#include <stdarg.h>

#define BUFF_SIZE 1024
/**
 * struct type_specifier - contains a type represented as char
 * @f: print_fucntion for specific type
 * @t: character representing type
 */
typedef struct type_specifier
{
	char t;
	char *(*f)(va_list args, char *mods);
} spec_t;
/**
 * struct flag_specifier - contains a flag and it's valid specifiers and func
 * @flag: flag represented as character
 * @specs: char pointer to array of valid specifiers for flag
 * @f: get_flag function that returns a char pointer and modifies a char *
 */
typedef struct flag_specifier
{
	char flag;
	char *specs;
	char *(*f)(char *);
} flag_t;
/**
 * struct print_helper_s - contains values needed in print helper
 * @format: pointer to format string
 * @f_i: pointer to index of format string
 * @buff: pointer to buffer
 * @c: pointer to character string, used by copy buffer
 * @buff_i: pointer to index of buffer
 * @busy: pointer to printf isbusy
 * @beg_i: pointer to beginning index (where % was found)
 * @buff_len: Counter for the total amount of characters so far.
 * @flags: pointer to int array pertaining to flag's being used
 * @mods: pointer to char array pertaining to modifiers being used (l and h)
 * @width: width pulled from format string
 * @precision: precision pulled from format string
 * @dot: boolean value 0 or 1 representing precision dot found or not
 * @spec_c: Counter for number of non flag characters encountered during busy
 */
typedef struct print_helper_s
{
	/* string  values */
	const char *format;
	char *buff;
	char *c;
	/* boolean values */
	char dot;
	char busy;
	/* integer values */
	unsigned int f_i;
	unsigned int buff_i;
	unsigned int beg_i;
	unsigned int buff_len;
	int width;
	int precision;
	int spec_c;
	/* flags & mods are pointers to arrays of booleans */
	int *flags;
	char *mods;
} printh_t;

int _printf(const char *format, ...);
int handle_alpha_percent(printh_t *help_s, va_list args);
char *create_buff(unsigned int bytes);
unsigned int copy_buff(char *str, printh_t *help_s);
unsigned int print_buff(char *buff, unsigned int buff_size);
void free_all(printh_t *help_s, va_list args);
void exit_busy_reset(printh_t *help_s, int reset_mods);
void get_width_precision(printh_t *help_s, va_list args);
void insert_null_char(printh_t *help_s);
char *(*get_string_func(char ch))(va_list, char *modifiers);
char *(*get_flag_func(int flag_index, char spec))(char *);
char *perform_flag_funcs(int *flags, char *str, char spec);
char *get_char(va_list, char *mods);
char *get_string(va_list, char *mods);
char *get_nonprint_string(va_list, char *mods);
char *get_percent(va_list, char *mods);
char *get_int(va_list, char *mods);
char *get_binary(va_list, char *mods);
char *get_unsigned(va_list, char *mods);
char *get_octal(va_list, char *mods);
char *get_hex(va_list, char *mods);
char *get_hex_upper(va_list, char *mods);
char *get_pointer(va_list, char *mods);
char *get_reverse(va_list, char *mods);
char *get_rot(va_list, char *mods);
char *do_plus_flag(char *str);
char *do_spc_flag(char *str);
char *do_octal_flag(char *str);
char *do_hex_flag(char *str);
char *do_hex_upper_flag(char *str);
char *do_width(char *str, int width, int space);
char *do_precision(char *str, int precision, char spec);
char *get_hex_n(unsigned int);
char *get_hex_long_n(unsigned long int);
char *do_shift(char *str, int width);
int ch_in_array(char c, char *ptr);
int is_specifier(char c);
int is_flag(char c, char prev_c);
int is_modifier(char c);
int _isalpha(char c);
int _isdigit(char c);
int is_printable(char c);
unsigned int _abs(int n);
int _strlen(char *s);
void _string_upper(char *str);
char *_strcpy(char *dest, char *src);
int fill_nonprint_buffer(int length, char *buff, char *str);
int get_numbase_len(unsigned int num, unsigned int base);
int get_longnumbase_len(unsigned long int num, unsigned int base);
void fill_numbase_buff(unsigned int, unsigned int, char *b, int size);
void fill_longnumbase_buff(unsigned long int num, unsigned int, char *, int);
#endif /* _PRINTF_H_ */
