#include "../../includes/minishell.h"

int prepare_command_struct(t_shell *mini, char *input);
static int count_pipes(char *input);
static int commands_init(t_shell *mini, int count);
static int initialize_command(t_cmd *cmd);
static int clean_cmds(t_cmd **cmds);


int prepare_command_struct(t_shell *mini, char *input)
{
	int pipe_count = count_pipes(input) + 2;
	mini->command_count = pipe_count;
	mini->cmds = ft_calloc(pipe_count, sizeof(t_cmd));
	if(!mini->cmds)
	{
		ft_putendl_fd("Failed to allocate memory for commads array", 2);
		return (1);
	}
	if(commands_init(mini, pipe_count))
		return (1);
	return (0);
}

static int count_pipes(char *input)
{
	int i = 0;
	int count = 0;

	while(input && input[i])
	{
		if(input[i] == '|' && !check_quotes(input, i))
			count++;
		i++;
	}
	return (count);
}

static int commands_init(t_shell *mini, int count)
{
	int i = 0;
	while(i < count)
	{
		mini->cmds[i] = malloc(sizeof(t_cmd));
		if(!mini->cmds[i])
		{
			ft_putendl_fd("Failed to allocate memory for struc", 2);
			clean_cmds(mini->cmds);
			return (1);
		}
		initialize_command(mini->cmds[i]);
		i++;
	}
	mini->cmds[count] = NULL;
	return (0);
}

static int initialize_command(t_cmd *cmd)
{
	cmd->command = NULL;
	cmd->path = NULL;
	cmd->args = NULL;
	cmd->arg_num = 0;
	cmd->exit = 0;
	cmd->index = 0;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (0);
}

static int clean_cmds(t_cmd **cmds)
{
	int i = 0;
	while(cmds && cmds[i])
	{
		if(cmds[i]->command)
			free(cmds[i]->command);
		if(cmds[i]->path)
			free(cmds[i]->path);
		if(cmds[i]->args)
			free(cmds[i]->args);
		free(cmds[i]);
		i++;
	}
	free(cmds);
	cmds = NULL;
	return (0);
}
