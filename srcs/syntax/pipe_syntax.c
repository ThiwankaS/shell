#include "../../includes/minishell.h"

/**
 * function declaration
 * The primary goal of these functions is to ensure that the user's input regarding pipes is syntactically correct.
 * It checks for common pipe-related errors, such as:
 *  - Starting with a pipe: A command line should not begin with a pipe.
 *  - Consecutive pipes: Two or more pipes in a row are invalid.
 *  - Trailing pipes: A command line should not end with a pipe
*/
int check_pipes(t_shell *mini, char **input);
static int check_consecutive_pipes(t_shell *mini, char *input);
static int check_pipe_error(t_shell *mini, char *input, int i);
static int check_trainling_pipe(t_shell *mini, char **input);

/**
 * Skips leading whitespaces.
 * Checks if the input starts with a pipe (|).
 * Calls check_consecutive_pipes to check for consecutive pipes.
 * Calls check_trainling_pipe to handle trailing pipes.
 * Returns 1 if an error is found, 0 otherwise.
*/
int check_pipes(t_shell *mini, char **input)
{
	size_t i = 0;

	i = skip_whitespaces(*input, i);

	if((*input)[i] == '|' && !check_quotes(*input, i))
	{
		ft_putendl_fd("syntax error near unexpected token ", 2);
		mini->exit_stat = 2;
		return (1);
	}

	if(check_consecutive_pipes(mini, *input))
		return (1);

	if(check_trainling_pipe(mini, input))
		return (1);

	return (0);
}

/**
 * This function checks for consecutive pipe characters.
 * Iterates through the input string.
 * When a pipe is found, it calls check_pipe_error to check for consecutive pipes.
 * It uses a pipe_found variable to track if the previous character was a pipe.
 * Returns 1 if consecutive pipes are found, 0 otherwise.
*/
static int check_consecutive_pipes(t_shell *mini, char *input)
{
	size_t i = 0, pipe_found = 0;

	while(input && input[i])
	{
		if(input[i] == '|' && !check_quotes(input, i))
		{
			if(check_pipe_error(mini, input, i))
				return (1);
			pipe_found = 1;
		}
		else if(ft_isspace(input[i]))
			pipe_found = 0;
		i++;
	}
	return (0);
}

/**
 * This function checks if the character after a pipe is also a pipe.
 * Skips whitespaces after the current pipe.
 * Checks if the next character is also a pipe.
 * If it is, it prints an error message and sets the exit status.
 * Returns 1 if consecutive pipes are found, 0 otherwise.
*/
static int check_pipe_error(t_shell *mini, char *input, int i)
{
	int j = i + 1;
	j = skip_whitespaces(input, j);
	if(input[j] == '|' && !check_quotes(input, j))
	{
		ft_putendl_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(&input[i], 2);
		mini->exit_stat = 2;
		return (1);
	}
	return (0);
}

/**
 * This function checks for a trailing pipe at the end of the input.
 * Iterates from the end of the input string, skipping trailing whitespace.
 * If the last non-whitespace character is a pipe, it calls handle_trailing_pipes.
 * if handle_trailing_pipes returns NULL, it means an error occured.
 * returns 1 if an error occured, 0 otherwise.
*/
static int check_trainling_pipe(t_shell *mini, char **input)
{
	int i = ft_strlen(*input) - 1;
	char *updated_input;
	while(i >=0 && ft_isspace((*input)[i]))
		i--;
	if(i >= 0 && (*input)[i] == '|' && !check_quotes(*input, i))
	{
		updated_input = handle_trailing_pipes(mini, *input);
		if(!updated_input)
		{
			*input = NULL;
			return (1);
		}
		*input = updated_input;
	}
	return (0);
}
