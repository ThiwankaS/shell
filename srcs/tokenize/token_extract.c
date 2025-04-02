#include "../../includes/shell.h"

int extract_tokens(t_list **tokens, char *input)
{
	int i = 0;

	/**
	 * first trying to extract a token bas on space/(' ')/ASCII INT 32 character
	*/
	char *line = ft_strtrim(input, " ");
	char **words = ft_split(line, '|');
	while(words && words[i])
	{
		*tokens = list_add_back(*tokens, ft_strtrim(words[i], " "));
		i++;
	}
	return (0);
}
