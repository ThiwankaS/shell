#include "../includes/minishell.h"

/**
 * main entry point o the program. vadilation ensure ./minishell does not require any additional
 * command line input.
 * argc - no of command line arguments including the program name it self
 * argv - string array consist of all the command line arguments including the program name
 * envp - array of strings consist of all the values accessibale through getenv()
 */

//volatile sig_atomic_t g_sig = 0;

int main(int argc, char *argv[], char **envp)
{
	int status = 0;

	(void)argv;
	if(argc != 1)
	{
		printf("<no arguments required !>\n");
		return (EXIT_FAILURE);
	}
	activate_shell(status, envp);
	return (EXIT_SUCCESS);
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


