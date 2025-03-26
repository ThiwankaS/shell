#include "../../../includes/minishell.h"

/**
 *list_env function will create one node storing all the informtin one string holds
 *in envp add respective node to the list
*/
t_env *list_env(char **envp)
{
	t_env *node;
	t_env *list = NULL;
	int i = 0;
	while(envp[i])
	{
		node = add_node(envp[i]);
		if(!node)
		return (NULL);
		ft_env_lstadd_back(&list, node);
		i++;
	}
	return (list);
}
