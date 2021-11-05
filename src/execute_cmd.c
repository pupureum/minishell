#include "minishell.h"

extern t_minishell	g_shell;

void	run_execve(t_cmd *cmd)
{
	char	**str;
	int		len;
	int		i;
	t_list	*curr;

	len = ft_lstsize(cmd->args);
	str = (char **)malloc(sizeof(char *) * (len + 2));
	if (str == NULL)
		error(MALLOC_ERROR);
	str[0] = ft_strjoin("/bin/", cmd->cmd);
	i = 1;
	curr = cmd->args;
	while (i <= len)
	{
		str[i] = curr->content;
		i++;
		curr = curr->next;
	}
	str[i] = NULL;
	execve(str[0], str, NULL);
	printf("bash: %s: command not found\n", cmd->cmd);
	exit(1);
}

int	fork_cmd(t_cmd *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		run_execve(cmd);
	else if (pid < 0)
		error(FORK_ERROR);
	waitpid(pid, &status, 0);
	return (status);
}

void	execute_cmd(t_AST_Node *node)
{
	int	result;

	if (ft_strncmp(((t_cmd *)(node->content))->cmd, "cd", 3) == 0)
		result = run_cd((((t_cmd *)(node->content))->args));
	else if (ft_strncmp(((t_cmd *)(node->content))->cmd, "env", 4) == 0)
		get_env(g_shell.env_list);
	else if (ft_strncmp(((t_cmd *)(node->content))->cmd, "export", 7) == 0)
		result = run_export((((t_cmd *)(node->content))->args),
				g_shell.export_list, g_shell.env_list);
	else if (ft_strncmp(((t_cmd *)(node->content))->cmd, "unset", 6) == 0)
		result = run_unset((((t_cmd *)(node->content))->args),
				&g_shell.export_list, &g_shell.env_list);
	else if (ft_strncmp(((t_cmd *)(node->content))->cmd, "pwd", 4) == 0)
		result = get_pwd();
	else
		result = fork_cmd(((t_cmd *)(node->content)));
	if (result != SUCCESS)
		g_shell.exit_status = result;
}
