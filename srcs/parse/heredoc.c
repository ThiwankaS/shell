#include "../../includes/minishell.h"

int restore_and_cleanup(t_shell *mini, int fd, int exit_code)
{
	if(fd != -1)
		close(fd);
	if(mini->stdin_saved != -1)
	{
		if(dup2(mini->stdin_saved, STDIN_FILENO) == -1)
			perror("Failed to restore original STDIN");
		close(mini->stdin_saved);
		mini->stdin_saved = -1;
	}
	return (exit_code);
}
