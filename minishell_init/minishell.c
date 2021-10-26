// #include "interpreter.h"
#include "minishell.h"

void	print_error(int error_code)
{
	if (error_code == MALLOC_ERROR)
		printf("Error: MALLOC FAILED\n");
}

void	error(int error_code)
{
	print_error(error_code);
	exit(error_code);
}

void	loop_minishell(struct termios *org, struct termios *new)
{
	t_list	*AST;

	while (1)
	{
		if (set_term_mode(new) == TERMIOS_ERROR)
			error(TERMIOS_ERROR);
		g_shell.line = readline("minishell> ");
		if (g_shell.line == NULL)
		{
			write(STDOUT_FILENO, "\033[1A", 4);
			write(STDOUT_FILENO, "minishell> exit\n", 16);
			break ;
		}
		if (set_term_mode(org) == TERMIOS_ERROR)
			error(TERMIOS_ERROR);
		add_history(g_shell.line);
		AST = parse_line(g_shell.line);
		if (AST == NULL)
			error(PARSE_ERROR);
		ft_lstclear(AST, del());
		execute(AST);
		free(g_shell.line);
	}
}

void	handler(int signum)
{
	if (signum == SIGQUIT)
		return ;
	else if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (rl_on_new_line() == -1)
			error(RL_ERROR);
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list			*AST;
	struct termios	org_term;//canon
	struct termios	new_term;//noncanon

	(void)argc;
	(void)argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	if (init_envp(envp) == MALLOC_ERROR)
		error(MALLOC_ERROR);
	if (init_term(&org_term, &new_term) == TERMIOS_ERROR)
		error(TERMIOS_ERROR);
	loop_minishell(&org_term, &new_term);
	return (0);
}
