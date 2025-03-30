#include "../../includes/minishell.h"

int check_redirects(t_shell *mini,char *input);
static int check_in_redirect(t_shell *mini, char *input, int *index);
static int check_out_redirect(t_shell *mini, char *input, int *index);
static int validate_redirect(t_shell *mini, char *input, int *index, char *type);

int check_redirects(t_shell *mini,char *input) {
	int i = 0;

	while(input[i])
	{
		if(input[i] == '>' && !check_quotes(input, i)) {
			if(check_in_redirect(mini, input, &i))
				return (1);
		}
		if(input[i] == '<' && !check_quotes(input, i)) {
			if(check_out_redirect(mini, input, &i))
				return (1);
		}
		i++;
	}
	return (0);
}

static int check_in_redirect(t_shell *mini, char *input, int *index)
{
	if(input[*index + 1] == '>')
	{
		(*index)++;
		if(validate_redirect(mini, input, index, ">>"))
			return (1);
	}
	else
	{
		if(validate_redirect(mini, input, index, ">"))
			return (1);
	}
	return (0);
}

static int check_out_redirect(t_shell *mini, char *input, int *index)
{
	if(input[*index + 1] == '<')
	{
		(*index)++;
		if(validate_redirect(mini, input, index, "<<"))
			return (1);
	}
	else
	{
		if(validate_redirect(mini, input, index, "<"))
			return (1);
	}
	return (0);
}

static int validate_redirect(t_shell *mini, char *input, int *index, char *type)
{
	(*index)++;
	(*index) = skip_whitespaces(input, (*index));
	if(!input[*index] || input[*index] == '|' || input[*index] == '>' || input[*index] == '<')
	{
		ft_putendl_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(type,2);
		mini->exit_stat = 2;
		return (1);
	}
	return (0);
}
