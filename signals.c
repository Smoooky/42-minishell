#include "includes/parser.h"

void	sig_int(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	here_sig(int signal)
{
	printf("heresig\n");
	if (signal == SIGINT)
	{
		stop_here_loop = 0;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	child_sig(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		write(1, "\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		(void)signal;
		write(2, "Quit:\n", 6);
	}
}
