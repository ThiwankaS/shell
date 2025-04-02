#include "includes/shell.h"

int main (void)
{
	char *input;
	//char *str;
	int res;

	while((input = readline("@so_thiwanka > ")))
	{
		add_history(input);
		res = input_validate(input);
		if(res)
			ft_printf("Invalid\n");
		else
			ft_printf("Valid\n");
	}
	return (0);
}
