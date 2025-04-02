#include "../../includes/minishell.h"

void unlink_all_heredocs(t_shell *mini)
{
	int i = 0;
	t_redir *current;

	while(i < mini->command_count)
	{
		current = mini->cmds[i]->redir_head;
		while(current)
		{
			if(current->type == HEREDOC)
			{
				if(current->heredoc_name)
				{
					unlink(current->heredoc_name);
					free(current->heredoc_name);
					current->heredoc_name = NULL;
				}
			}
			current = current->next;
		}
		i++;
	}
}
