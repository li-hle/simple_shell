#include "shell.h"

/**
 * get_environ - function returns the string array copy of our environ
 * @info: this is the structure containing potential arguments
 * Used to maintain constant function prototype.
 * Return: Always return 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - this removes an environment variable
 * @info: this is the structure containing potential arguments
 * Used to maintain constant function prototype
 * @var: the string env var property
 * Return: return 1 on delete, else 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t v = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), v);
			v = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		v++;
	}
	return (info->env_changed);
}

/**
 * _setenv - this initialize a new environment variable
 * or modify an existing one
 * @info: this is structure containing potential arguments
 * Used to maintain constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always return 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
