#include "../../includes/minishell.h"

/**
 * Designed to deal with a situation where the user's input ends with a pipe (|).
 * In a typical shell, a trailing pipe indicates that the user intends to provide more commands to be piped into the last command.
 * This function handles the prompting and reading of that additional input.
*/
char *handle_trailing_pipes(t_shell *mini, char *input)
{
	char *additional_input = NULL;
	signal(SIGINT, sig_handler_hd);
	mini->stdin_saved = dup(STDIN_FILENO);
	if(mini->stdin_saved == -1)
	{
		perror("Failed to save STDIN");
		return (NULL);
	}
	while (true)
	{
		additional_input = readline("> ");
		if(!additional_input || g_sig == SIGINT)
		{
			g_sig = 0;
			mini->exit_stat = restore_and_cleanup(mini, -1, 1);
			free(input);
			return (NULL);
		}
	}
	return (additional_input);
}
