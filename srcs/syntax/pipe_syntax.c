#include "../../includes/minishell.h"

/**
 * function declaration
*/
int check_pipes(t_shell *mini, char **input);
static int check_consecutive_pipes(t_shell *mini, char **input);

int check_pipes(t_shell *mini, char **input) {
	size_t i = 0;

	i = skip_whitespaces(*input, i);

	if((*input)[i] == '|' && !check_quotes(*input, i)) {
		ft_putendl_fd("syntax error near unexpected token ", 2);
		mini->exit_stat = 2;
		return (1);
	}

	if(check_consecutive_pipes(mini, *input))
		return (1);
	return (0);
}

static int check_consecutive_pipes(t_shell *mini, char **input) {
	size_t i = 0, pipe_found = 0;

	while(input && input[i])
	{
		i++;
	}
	return (0);
}
