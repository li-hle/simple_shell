#include "shell.h"

/**
 * _erratoi - the function converts a string to an integer
 * @s: string to be converted
 * Return: return 0 if no numbers in string
 * converted number otherwise -1 on error
 */
int _erratoi(char *s)
{
	int v = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (v = 0;  s[v] != '\0'; v++)
	{
		if (s[v] >= '0' && s[v] <= '9')
		{
			result *= 10;
			result += (s[v] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - this prints an error message
 * @info: parameter & return info struct
 * @estr: the string containing specified error type
 * Return: return 0 if no numbers in string
 * converted number otherwise -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - the function prints a decimal (integer) number (base 10)
 * @input: this is the input
 * @fd: this is the filedescriptor to write to
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int v, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (v = 1000000000; v > 1; v /= 10)
	{
		if (_abs_ / v)
		{
			__putchar('0' + current / v);
			count++;
		}
		current %= v;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - the function converter function, a clone of itoa
 * @flags: argument flags
 * @num: the number
 * @base: the base
 * Return: return the string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - this function replaces first instance of '#' with '\0'
 * @buf: the address of the string to modify
 * Return: Always return 0;
 */
void remove_comments(char *buf)
{
	int v;

	for (v = 0; buf[v] != '\0'; v++)
		if (buf[v] == '#' && (!v || buf[v - 1] == ' '))
		{
			buf[v] = '\0';
			break;
		}
}
