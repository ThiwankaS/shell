#include "../../../includes/minishell.h"

/**
 * function declarations
*/
int clean_env(t_env *node);
int fill_node(t_env *node, char *name, char *value);
static int set_name(t_env *node, char *name);
static int set_value(t_env *node, char *value);

int fill_node(t_env *node, char *name, char *value)
{
	if(set_name(node, name))
	{
		clean_env(node);
		free(name);
		return (1);
	}
	if (set_value(node, value))
	{
		clean_env(node);
		return (1);
	}
	return (0);
}

/**
 *Will set the name variable of the node
*/
static int set_name(t_env *node, char *name)
{
	node->name = ft_strdup(name);
	if(!node->name)
		return (1);
	return (0);
}
/**
 * Will set the value variable of the node in the event value is NULL value will be set
 * to an empty string
*/
static int set_value(t_env *node, char *value)
{
	if(value)
	{
		node->value = ft_strdup(value);
		if(!node->value)
			return (1);
		return (0);
	}
	else
	{
		node->value = ft_strdup(" ");
		if(!node->value)
			return (1);
		return (0);
	}
	return (0);
}

int clean_env(t_env *node)
{
	t_env *current;
	while(node != NULL)
	{
		current = node;
		free(node->name);
		free(node->value);
		node = node->next;
		free(current);
	}
	return (0);
}
