#include "../../includes/minishell.h"

int split_input_by_pipe(t_shell *mini, char *input);
static int segment_handler(t_cmd *cmd, char *input, int start, int i);
static char *ft_strndup(char *input, int start, int i);
static char *trim_whitespaces(char *str);

int split_input_by_pipe(t_shell *mini, char *input)
{
	int i = 0, start = 0, index = 0;

	while(input[i])
	{
		if(input[i] == '|' && !check_quotes(input, i))
		{
			if(segment_handler(mini->cmds[index], input, start, i))
				return (1);
			start = i + 1;
			index++;
		}
		i++;
	}

	if(segment_handler(mini->cmds[index], input, start, i))
		return (1);
	return (0);
}

static int segment_handler(t_cmd *cmd, char *input, int start, int i)
{
	char *trimmed = ft_strndup(input, start, i);
	if(!trimmed)
	{
		ft_putendl_fd("Failed to allocate memory for the trimmed string", 2);
		return (1);
	}
	trimmed = trim_whitespaces(trimmed);
	cmd->seg = trimmed;
	if(!cmd->seg)
	{
		ft_putendl_fd("No seg in the cmd struct", 2);
		free(trimmed);
		return (1);
	}
	return (0);
}

static char *ft_strndup(char *input, int start, int i)
{
	int size = i - start + 1;
	char *str = malloc(sizeof(char) * size);
	if(!str)
	{
		ft_putendl_fd("Failed to allocate memory for the command string", 2);
		return (NULL);
	}
	int j = start;
	while(input && input[j] && j < i)
	{
		str[j] = input[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static char *trim_whitespaces(char *str)
{
	int start = 0, len = ft_strlen(str), end = 0;

	if(!str)
		return (NULL);
	while(str[start] && ft_isspace(str[start]))
		start++;
	end = len - 1;
	while(str[end] && ft_isspace(str[end]) && end >= start)
		end--;
	len = end - start + 1;
	ft_memmove(str, str + start, len);
	str[len] = '\0';
	return (str);
}
