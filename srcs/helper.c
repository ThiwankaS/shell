#include "../includes/minishell.h"

int activate_shell(int status, char **envp)
{
	t_shell *mini = ft_calloc(1, sizeof(t_shell));
	if(!mini)
	{
		ft_putendl_fd("mini struct memomry allocation failed!", 2);
		status = 1;
		return(status);
	}
	if(init_shell(mini, envp))
	{
		status = 1;
		return(status);
	}
	free(mini);
	return (0);
}

int init_shell(t_shell *mini, char **envp)
{
	mini->env = list_env(envp);
	if(!mini->env)
	{
		mini_cleaner(mini);
		free(mini);
		return (1);
	}
	return (0);
}
