#include "../../includes/minishell.h"

int parse_input(t_shell *mini);
static int parse_cmd_string(t_shell *mini, t_cmd *cmd);
static int cmd_string(t_shell *mini, t_cmd *cmd, int i, int *cmd_found);

int parse_input(t_shell *mini)
{
	int index = 0;

	while(mini->cmds[index])
	{
		mini->cmds[index]->index = index;
		if(parse_cmd_string(mini, mini->cmds[index]))
		{
			mini->exit_stat = 1;
			unlink_all_heredocs(mini);
			clean_cmds(mini->cmds);
			return (1);
		}
		index++;
	}
	return (0);
}

static int parse_cmd_string(t_shell *mini, t_cmd *cmd)
{
	int i = 0, cmd_found = 0;

	if(handle_expand(mini, &cmd))
		return (1);
	i = cmd_string(mini, cmd, i, &cmd_found);
	if(i == -1)
		return (1);
	if(cmd_found && (!cmd->args || !cmd->args[0]))
		i = no_argc(cmd , i);
	return (0);
}

static int cmd_string(t_shell *mini, t_cmd *cmd, int i, int *cmd_found)
{
	while (cmd->seg[i])
	{
		if(is_redirection(cmd, i))
		{
			i = handle_redirections(mini, cmd, i);
			if(i == -1)
				return (-1);
			i = skip_whitespaces(cmd->seg, i);
		}
		else if (*cmd_found == 0)
		{
			i = handle_cmd_name(cmd, i);
			if(i == -1)
				return (-1);
			*cmd_found = 1;
		}
		else
		{
			i = handle_cmd_args(mini, cmd, i);
			if(i == -1)
				return (-1);
		}
	}
	return(i);
}
