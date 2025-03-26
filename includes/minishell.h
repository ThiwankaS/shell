#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../ft_libft/libft.h"
# include "../ft_libft/ft_printf.h"
# include "../ft_libft/get_next_line.h"

// typedef struct s_cmd
// {
// 	char *text;
// };


char **ft_split(const char *s, char c);

size_t ft_strlen(const char *s);

int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strcmp(const char* s1, const char* s2);

#endif
