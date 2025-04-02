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
 * data node strucutre to hold the tokens extract from input, this node will make a linked list
*/
typedef struct s_list
{
	char *token;
	struct s_list *next;
} t_list;

typedef struct s_cmd
{
	char *command;
	char **args;
	struct s_cmd *next;
} t_cmd;

typedef struct s_shell
{
	char **envp;
	t_list *tokens;
} t_shell;


void print(t_list *list, char *msg);

/**
 * Implementaion in srcs/validate/surround.c
*/
int input_validate(char *input);
char *in_quotes(char *input);

/**
 * Implementaion in srcs/error/syntax_errors.c
*/
int syntax_error(char *msg);

/**
 * Implementation in srcs/helper.c
*/
int activate_shell(char *input, char **envp);

/**
 * Implementation in srcs/tokenize/token_list.c
*/
t_list *list_add_back(t_list *list, char *str);
int extract_tokens(t_list **tokens, char *input);

/**
 * Implementation in srcs/parse/parser.c
*/
int parse_and_expand(t_shell *mini);

#endif
