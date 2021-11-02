/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:59:10 by bylee             #+#    #+#             */
/*   Updated: 2021/11/02 20:24:50 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_exe_proc(int idx_cmd, int **fd_pipe, t_AST_Node *node)
{
	//redir_and_exe(idx_cmd, node);
	exit(EXIT_SUCCESS);
}

void	create_cmd_proc(int idx_cmd, int nums_cmd, int **fd_pipe, t_AST_Node *node)
{
	pid_t	pid;
	int		status;

	if (hookup_pipes(idx_cmd, fd_pipe, nums_cmd))
		exit(FD_DUP_ERROR);
	close_fd_table(nums_cmd, fd_pipe, idx_cmd);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		create_exe_proc(idx_cmd, fd_pipe, node);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		exit(PROCESS_ERROR);
	exit(EXIT_SUCCESS);
}

int	wait_procs(int nums_cmd, pid_t *pids)
{
	int		status;
	int		idx_cmd;

	idx_cmd = -1;
	while (++idx_cmd < nums_cmd)
	{
		waitpid(pids[idx_cmd], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

int	create_procs(t_AST_Node *node, int **fd_pipe, int nums_cmd)
{
	pid_t	*pids;
	int		idx_cmd;

	idx_cmd = -1;
	pids = (pid_t *)malloc(sizeof(pid_t) * nums_cmd);
	if (pids == NULL)
		return (MALLOC_FAILURE);
	while (++idx_cmd < nums_cmd)
	{
		pids[idx_cmd] = fork();
		if (pids[idx_cmd] < 0)
			return (FORK_ERROR);
		else if (pids[idx_cmd] == 0)
		{
			if (idx_cmd != nums_cmd - 1)
				create_cmd_proc(idx_cmd, nums_cmd, fd_pipe, ((t_pipe *)(node->content))->leftchild);
			else
				create_cmd_proc(idx_cmd, nums_cmd, fd_pipe, node);
		}
		node = ((t_pipe *)(node->content))->rightchild;
	}
	close_fd_table(nums_cmd, fd_pipe, -1);
	return (wait_procs(nums_cmd, pids));
}

int	build_pipeline(t_AST_Node *node, int nums_cmd)
{
	int	result;
	int	**fd_pipe;

	result = 0;
	fd_pipe = malloc_fd_table(nums_cmd);
	if (fd_pipe == NULL)
		error_exit(MALLOC_FAILURE);
	if (fill_fd_table(nums_cmd, fd_pipe))
		error_exit(PIPE_FAILURE);
	if (create_procs(node, fd_pipe, nums_cmd))
		error_exit(PROCESS_ERROR);
	free_fd_table(fd_pipe);
	return (result);
}
