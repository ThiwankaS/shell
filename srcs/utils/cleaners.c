#include "../../includes/minishell.h"

void mini_cleaner(t_shell *mini)
{
	if(mini->env)
		clean_env(mini->env);
	if(mini->cmds)
		clean_cmds(mini->cmds);
}
