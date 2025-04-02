#include "../../includes/shell.h"

void expand(t_cmd *cmd, t_list *list);
int ft_strnmcpy(char **dest, char *src, int n, int m);

int parse_and_expand(t_shell *mini)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if(!cmd)
		return (1);
	print(mini->tokens, "final token");
	expand(cmd, mini->tokens);
	return (0);
}

void expand(t_cmd *cmd, t_list *list)
{
	int n1 = 0, n2 = ft_strchr(list->token, ' ') - list->token;
	printf("n1 : %d\n", n1);
	printf("n2 : %d\n", n2);
	int res = ft_strnmcpy(&cmd->command, list->token, n1, n2);
	printf("%s\n", cmd->command);
	printf("res : %d\n", res);
}

int ft_strnmcpy(char **dest, char *src, int n, int m)
{
	int i = 0;

	if (n >= m || !src || !dest)
		return (-1);

	*dest = malloc(sizeof(char) * (m - n + 1));
	if (!*dest)
		return (-1);

	while ((i + n) < m && src[i + n])
	{
		(*dest)[i] = src[i + n];
		i++;
	}
	(*dest)[i] = '\0';
	return (i);
}
