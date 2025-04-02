#include "includes/shell.h"

int main (int ac, char **av, char **envp)
{
	char *input;
	int status = 0;

	(void)av;
	if(ac == 1)
	{
		while((input = readline("@so_thiwanka > ")))
		{
			add_history(input);
			status = activate_shell(input, envp);
			free(input);
		}
	}
	return (status);
}

void print(t_list *list, char *msg)
{
	printf("\n%s\n", msg);
	t_list *current = list;
	while(current)
	{
		printf("%s\n", current->token);
		current = current->next;
	}
	printf("------------------------------------\n");
}
