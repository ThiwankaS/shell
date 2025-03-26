#include "../../../includes/minishell.h"

/**
 *
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
