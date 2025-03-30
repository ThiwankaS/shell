#include "../../includes/minishell.h"

int parse_and_validate_input(t_shell *mini, char **input) {
	if(valid_input_syntax(mini, input))
		return (1);
	return (0);
}
