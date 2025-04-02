#include "includes/minishell.h"

int activate_shell(int status, char **envp);
int init_shell(t_shell *mini, char **envp);
int user_prompt(t_shell *mini, int status);
static int is_this_empty(char *str);
static int handle_input(t_shell *mini,char* input);

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
	status = user_prompt(mini, status);
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
		ft_putendl_fd("envp creation failed!", 2);
		return (1);
	}
	mini->exit_stat = 0;
	return (0);
}

int user_prompt(t_shell *mini, int status)
{
	char *input;

	while(true)
	{
		// if(isatty(0)) //can not use the fileno(stdin) because fileno is not a allowed function
		sig_init();
		input = readline("~minishell~ >");
		if(input == NULL)
			break;
		if(is_this_empty(input))
		{
			free(input);
			continue;
		}
		if(input && *input)
		{
			if(handle_input(mini, input))
				continue;
		}
	}
	status = mini->exit_stat;
	return (status);
}

static int is_this_empty(char *str)
{
	if(strncmp(" ", str, 1) == 0)
		return (1);
	return (0);
}

static int handle_input(t_shell *mini,char* input)
{
	add_history(input);
	if(parse_and_validate_input(mini, &input))
	{
		free(input);
		return (1);
	}
	free(mini);
	free(input);
	return(0);
}

static char *in_single_quotes(char *input)
{
	int start = 0, end = 0, len = 0;
	char *str = NULL;
	str = ft_strchr(input, '\'');
	if(!str)
		return (NULL);
	start = str - input;
	str = ft_strrchr(input, '\'');
	if(!str)
		return (NULL);
	end = str - input;
	len = end - start + 1;
	str = malloc(sizeof(char) * len);
	if(!str)
		return (NULL);
	ft_strlcpy(str, &input[start], (end - start + 2));
	return (str);
}

char *in_doubel_quotes(char *input)
{
	int start = 0, end = 0, len = 0;
	char *str = NULL;

	str = ft_strchr(input, '"');
	if(!str)
		return (NULL);
	start = str - input;
	str = ft_strrchr(input, '"');
	if(!str)
		return (NULL);
	end = str - input;
	len = end - start + 1;
	str = malloc(sizeof(char) * len);
	if(!str)
		return (NULL);
	ft_strlcpy(str, &input[start], (end - start + 2));
	return (str);
}

