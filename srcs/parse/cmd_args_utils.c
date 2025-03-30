#include "../../includes/minishell.h"

size_t skip_whitespaces(const char *str, size_t i)
{
	while(str && str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}
