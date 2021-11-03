#include "command.h"
extern t_minishell g_shell;

int	do_fork(int flag, t_list *args)
{
	int	pid;
	int	result;

	pid = fork();
	if (!pid)
	{
		if (flag == PWD)
			result = get_pwd();
		else if (flag == ECHO)
			result = run_echo(args);
		if (result == 1)
		{
			printf("ECHO or PWD ERROR\n");
			return (1);
		}
		else if (result == MALLOC_ERROR)
			malloc_error();
	}
	else if (pid < 0)
	{
		printf("Fork Error");
		return (1);
	}
	wait(NULL);
	return (0);
}

int	idenfify_commands(char **envp, t_AST_Node *node)
{
	int	result;

	if (ft_strncmp(((t_cmd *)(node->content))->cmd, "pwd", 4) == 0)
		result = do_fork(PWD, (((t_cmd *)(node->content))->args));
	else if(ft_strncmp(((t_cmd *)(node->content))->cmd, "echo", 5) == 0)
		result = do_fork(ECHO, (((t_cmd *)(node->content))->args));
	else if(ft_strncmp(((t_cmd *)(node->content))->cmd, "cd", 3) == 0)
		result = run_cd((((t_cmd *)(node->content))->args->content));
	else if(ft_strncmp(((t_cmd *)(node->content))->cmd, "env", 4) == 0)
		get_env(envp);
	else if (ft_strncmp(((t_cmd *)(node->content))->cmd, "export", 7) == 0)
		result = run_export((((t_cmd *)(node->content))->args), g_shell.export_list, g_shell.env_list);
	else if (ft_strncmp(((t_cmd *)(node->content))->cmd, "unset", 6) == 0)
		result = run_unset((((t_cmd *)(node->content))->args), g_shell.export_list, g_shell.env_list);
	else
	{
		printf("Error : Invalid command");
		return (1);
	}
	if (result == 1)
		return (1);
	return (0);
}