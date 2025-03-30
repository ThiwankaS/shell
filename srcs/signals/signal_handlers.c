#include "../../includes/minishell.h"

void sig_handler(int signal);
void sig_handler_hd(int signal);
void sig_init(void);

void sig_init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void sig_handler_hd(int signal)
{
	close(STDIN_FILENO);
	g_sig = signal;
}

void sig_handler(int signal)
{
	if(signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}
