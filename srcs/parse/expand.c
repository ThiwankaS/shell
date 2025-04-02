#include "../../includes/minishell.h"

int handle_expand(t_shell *mini, t_cmd **cmd);
static char *ft_strjoin_char(char *str, char c);
static int this_is_space(t_cmd **cmd, t_expand *arg, char **expan);
static int exp_while(t_shell *mini, t_cmd **cmd, t_expand *arg, char **expan);

int handle_expand(t_shell *mini, t_cmd **cmd)
{
	char *expan = NULL;
	t_expand arg;

	if(init_expansion(&arg, &expan)) //need to implement
		return (1);
	if(exp_while(mini, cmd, &arg, &expan))
	{
		if(arg.value)
			free(arg.value);
		if(expan)
			free(expan);
		return (1);
	}
	free((*cmd)->seg);
	(*cmd)->seg = expan;
	return (0);
}

static int exp_while(t_shell *mini, t_cmd **cmd, t_expand *arg, char **expan)
{
	while((*cmd)->seg[arg->index])
	{
		if(arg->index != -1)
		{
			if(ft_isspace((*cmd)->seg[arg->index]) && !arg->dbl && !arg->sgl)
				arg->index = this_is_space(cmd, arg, expan);
			else if(((*cmd)->seg[arg->index] == '\'')||((*cmd)->seg[arg->index] == '"'))
				arg->index = quoted(mini, cmd, arg, expan);
			else if((*cmd)->seg[arg->index] == '<' && (*cmd)->seg[arg->index + 1] == '<')
				arg->index = hd(cmd, arg, expan);//need implementaion
			else
				arg->index = s_quoted(mini, cmd, arg, expan); //need implementaion
		}
		else
			return (1);
	}
	return (0);
}

static int this_is_space(t_cmd **cmd, t_expand *arg, char **expan)
{
	char *temp = *expan;

	*expan = ft_strjoin_char(temp, (*cmd)->seg[arg->index]);
	free(temp);
	if(!*expan)
		return (-1);
	arg->index++;
	return (arg->index);
}

static char *ft_strjoin_char(char *str, char c)
{
	size_t len = ft_strlen(str), i = 0;
	char *new = malloc(sizeof(char) * (len + 2));
	if(!new)
		return (NULL);
	while(str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i] = '\0';
	return (new);
}

static int quoted(t_shell *mini, t_cmd **cmd, t_expand *arg, char **expan)
{
	char *temp = *expan;

	arg->index = in_quotes(mini, (*cmd)->seg, arg->index, arg);
	if(arg->index == -1)
		return (-1);
	*expan = ft_strjoin(temp, arg->value);
	if(!*expan)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	free(arg->value);
	arg->value = NULL;
	return (arg->index);
}

static int in_quotes(t_shell *mini, char *str, int i, t_expand *arg)
{
	if(init_quoted(arg, i, str) == -1) //need implementaion
		return (-1);
	what_quotes(str, arg); //need implementaion
	while(str[arg->index])
	{
		if(!arg->sgl && !arg->dbl)
			break;
		if(arg->index == -1)
		{
			if(str[arg->index] == '$')
				arg->index = handel_dollar(mini, arg, str); //need implementaion
			else if((!arg->sgl && !arg->dbl && (str[arg->index] == '\'' || str[arg->index] == '"'))
				|| ((arg->sgl && str[arg->index] == '\'')||(arg->dbl && str[arg->index] == '"')))
			{
				arg->index = handle_quotes(arg, str); //need implementaion
			}
			else
			{
				if(add_char(str, arg)) //need implementaion
					return (-1);
			}
		}
		else
			return (-1);
	}
}

/**
 * init_expansion
 * hd
 * s_quoted
 * in_quotes
 * init_quoted
 * what_quotes
 * handel_dollar
 * handle_quotes
 * add_char
 *
*/
