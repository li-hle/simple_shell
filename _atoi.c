#include "shell.h"

/**
 * interactive - function returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, otherwise 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - function checks if character is delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: return 1 if true, otherwise 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - the function here checks for alphabetic character
 * @c: character to input
 * Return: return 1 if c is alphabetic, otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - the function here converts a string to an integer
 * @s: string to be converted
 * Return: return 0 if no numbers in string, else converted number
 */

int _atoi(char *s)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
