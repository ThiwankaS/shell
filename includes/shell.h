#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../ft_libft/libft.h"
# include "../ft_libft/ft_printf.h"
# include "../ft_libft/get_next_line.h"

/**
 * Implementaion in srcs/validate/surround.c
*/
int input_validate(char *input);
char *in_quotes(char *input);

/**
 * Implementaion in srcs/error/syntax_errors.c
*/
int syntax_error(char *msg);

#endif
