#include "../includes/minishell.h"

/**
 * main entry point o the program. vadilation ensure ./minishell does not require any additional
 * command line input.
 * argc - no of command line arguments including the program name it self
 * argv - string array consist of all the command line arguments including the program name
 * envp - array of strings consist of all the values accessibale through getenv()
 */

int main(int argc, char *argv[], char **envp) {
	int status = 0;

	(void)argv;
	if(argc != 1) {
		printf("<no arguments required !>\n");
		return (EXIT_FAILURE);
	}
	activate_shell(status, envp);
	return (EXIT_SUCCESS);
}
