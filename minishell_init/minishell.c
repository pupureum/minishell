#include "interpreter.h"

#define t_minishell	g_shell;


int	main(int argc, char *argv[], char *envp[])
{
	t_list *AST;

	(void)argc;
	(void)argv;
	init(envp);
	while (1)
	{
		read_line();
		if (g_shell.line == NULL)
			return (PARSE_ERROR)
		AST = parse_line(g_shell.line);
		if (AST == NULL)
		{
			printf("Parsing ERROR")
			return (PARSE_ERROR);
		}

		ft_lstclear(AST);
		AST->content
		execute(AST);
	}

	return (0);
}
