#include "sh.h"

int main(void)
{
	char *line;

	while ((line = readline("~ minishell ->")) != NULL)
	{
		if(ft_strcmp("exit", line) == 0)
			break;
		printf("%s\n", line);
	}
	free(line);
	return (0);
}
