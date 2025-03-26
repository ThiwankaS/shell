#include "../../includes/minishell.h"

/**
 * function declaration
*/
int valid_input_syntax(t_shell *mini,char **input);
static int check_quotes(char *input, size_t limit);

int valid_input_syntax(t_shell *mini,char **input)
{
	(void)mini;
	if(check_quotes(*input, ft_strlen(*input)))
	{
		ft_putendl_fd("syntax error : unmatch quotes", 2);
		mini->exit_stat = 2;
		return (1);
	}
	return (0);
}

static int check_quotes(char *input, size_t limit)
{
	int in_single_quote = 0;
	int in_double_quote = 0;
	int index = 0;

	while(input[index] && (limit == -1 || index < limit))
	{
		if(input[index] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[index] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		index++;
	}
	return (in_single_quote || in_double_quote);
}
