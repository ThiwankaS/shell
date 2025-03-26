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


/**
 *env node will store the environment variable data in the format of key value pair "SHELL=/bin/bash"
 *envp will split into key,value pairs and will be stored as one key,value pair as a node in a linked
 *list
*/
typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

/**
 * main data struture to store shell state
 * envp - pointer to envp data pass from the main program
*/
typedef struct s_shell
{
	t_env *env;
} t_shell;

/**
 *helper fucntions to initiate the program, implementaion on helper.c file
*/
int activate_shell(int status, char **envp);
int init_shell(t_shell *mini, char **envp);

/**
 *helper functions to create linked list to store the envp values a s key,pair
 *implementaion on env_ll.c file
*/
t_env *create_node(void);
t_env *add_node(char *env);
void ft_env_lstadd_back(t_env **lst, t_env *new);

t_env *list_env(char **envp);

int fill_node(t_env *node, char *name, char *value);

#endif
