#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef enum s_redir_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC
} t_redir_type;

typedef struct s_expand
{
	int  sgl;
	int  dbl;
	int  index;
	int  start;
	char *name;
	char *value;
} t_expand;


typedef struct s_redir
{
	char *file;
	char *delimiter;
	char *heredoc_name;
	int  heredoc_index;
	bool expand;
	t_redir_type type;
	struct s_redir *next;
} t_redir;


typedef struct s_cmd
{
	char *command;
	char *path;
	char **args;
	char *seg;
	int  arg_num;
	int  index;
	int  fd_in;
	int  fd_out;
	int  exit;
	t_redir *redir_head;
	t_redir *redir_tail;
} t_cmd;

/**
 *env node will store the environment variable data in the format of key value pair "SHELL=/bin/bash"
 *envp will split into key,value pairs and will be stored as one key,value pair as a node in a linked
 *list
*/
typedef struct s_env {
	char *name;
	char *value;
	struct s_env *next;
} t_env;

/**
 * main data struture to store shell state
 * envp - pointer to envp data pass from the main program
*/
typedef struct s_shell {
	t_env *env;
	int exit_stat;
	int stdin_saved;
	int command_count;
	t_cmd **cmds;
} t_shell;

/**
 *helper fucntions to initiate the program, implementaion on srcs/helper.c file
*/
int activate_shell(int status, char **envp);
int init_shell(t_shell *mini, char **envp);

/**
 *helper functions to create linked list to store the envp values a s key,pair
 *implementaion on srcs/built_in/env/env_ll.c file
*/
t_env *create_node(void);
t_env *add_node(char *env);
void ft_env_lstadd_back(t_env **lst, t_env *new);


/**
 * helper fucntions implementation srcs/built_in/env/env_handling.c
*/
t_env *list_env(char **envp);

/**
 * helper fucntions implementation srcs/built_in/env/env_utils.c
*/
int clean_env(t_env *node);
int fill_node(t_env *node, char *name, char *value);

/**
 * helper fucntions implementation srcs/utils/cleaners.c
*/
void mini_cleaner(t_shell *mini);

/**
 * helper fucntions implementation srcs/parse/parser.c
*/
int parse_and_validate_input(t_shell *mini, char **input);

/**
 * helper fucntions implementation srcs/syntax/syntax_checker.c
*/
int valid_input_syntax(t_shell *mini,char **input);
int check_quotes(char *input, int limit);

/**
 * helper fucntions implementation srcs/syntax/pipe_syntax.c
*/
int check_pipes(t_shell *mini, char **input);

/**
 * helper fucntions implementation srcs/parse/cmd_args_utils.c
*/
size_t skip_whitespaces(const char *str, size_t i);

/**
 * helper fucntions implementation srcs/syntax/tariling_pipe.c
*/
char *handle_trailing_pipes(t_shell *mini, char *input);

/**
 * helper fucntions implementation srcs/signals/signal_handlers.c
*/
void sig_init(void);
void sig_handler_hd(int signal);

/**
 * helper fucntions implementation srcs/parse/heredoc.c
*/
int restore_and_cleanup(t_shell *mini, int fd, int exit_code);

/**
 * helper fucntions implementation srcs/syntax/redirect_syntax.c
*/
int check_redirects(t_shell *mini,char *input);

/**
 * helper fucntions implementation srcs/commands/command_array.c
*/
int prepare_command_struct(t_shell *mini, char *input);
int clean_cmds(t_cmd **cmds);

/**
 * helper fucntions implementation srcs/parse/split_input.c
*/
int split_input_by_pipe(t_shell *mini, char *input);

/**
 * helper fucntions implementation  srcs/parse/parse_input.c
*/
int parse_input(t_shell *mini);

/**
 * helper fucntions implementation srcs/execute/pipeline_utils.c
*/
void unlink_all_heredocs(t_shell *mini);

/**
 * helper fucntions implementation srcs/parse/expand.c
*/

/* ############################################################### */

#endif
