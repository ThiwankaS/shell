#include "../../../includes/minishell.h"

/**
 * function declaration
*/
void ft_env_lstadd_back(t_env **lst, t_env *new);
t_env *create_node(void);
t_env *add_node(char *env);
static int check_and_free(void *ptr, void *ptr1, void *ptr2);

/**
 *ft_env_lstadd_back will add a new node to the link list ponited by **lst
*/
void ft_env_lstadd_back(t_env **lst, t_env *new) {
	t_env *node;

	if(!lst || !new)
		return;
	if(!*lst) {
		*lst = new;
		return;
	}
	node = *lst;
	while(node->next)
		node = node->next;
	node->next = new;
}

/**
 *create_node function allocate memory enough to store the data of t_env node
 *and return a pointer ot the node. Initial value of the varaibles will be NULL
*/
t_env *create_node(void)
{
	t_env *node = (t_env *) malloc(sizeof(t_env));
	if(!node)
		return (NULL);
	node->name = NULL;
	node->value = NULL;
	node->next = NULL;
	return (node);
}

/**
 *add_node function will add the data recived as a string env after split in to key and value
*/
t_env *add_node(char *env)
{
	char *name;
	char *value;
	t_env *node = create_node();
	char *sign = ft_strchr(env, '=');
	if(!node || !sign)
		return (NULL);
	name = ft_substr(env, 0, (sign - env));
	if(check_and_free(name, node, NULL))
		return (NULL);
	value = ft_strdup(sign + 1);
	if(check_and_free(value, name, node))
		return (NULL);
	if(fill_node(node, name, value))
	{
		free(value);
		return (NULL);
	}
	node->next = NULL;
	free(name);
	free(value);
	return (node);
}

/**
 *If case ptr is a invalid pointer the preceding memory will freed pointed by ptr1 and ptr2 prevent
 *memory leaks because, invalid ptr will triggered an exit from the program.
*/
static int check_and_free(void *ptr, void *ptr1, void *ptr2)
{
	if(!ptr)
	{
		if(ptr1)
			free(ptr1);
		if(ptr2)
			free(ptr2);
		return (1);
	}
	return (0);
}
