/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:59:10 by bylee             #+#    #+#             */
/*   Updated: 2021/10/28 12:34:40 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
int	nums_cmd = 3;

void	create_exe_proc(int idx_cmd, int **fd_pipe)
{
	// redirection 
	// execution
	exit(EXIT_SUCCESS);
}

int	hookup_pipes(int idx_cmd, int **fd_pipe)
{
	if (idx_cmd == 0)
	{
		if (dup2(fd_pipe[idx_cmd][1], STDOUT_FILENO) == -1)
			return (FD_DUP_ERROR);
	}
	else if (idx_cmd == nums_cmd - 1)
	{
		if (dup2(fd_pipe[idx_cmd - 1][0], STDIN_FILENO) == -1)
			return (FD_DUP_ERROR);
	}
	else
	{
		if (dup2(fd_pipe[idx_cmd][1], STDOUT_FILENO) == -1
			|| dup2(fd_pipe[idx_cmd - 1][0], STDIN_FILENO) == -1)
			return (FD_DUP_ERROR);
	}
	return (SUCCESS);
}

void	create_cmd_proc(int idx_cmd, int **fd_pipe)
{
	pid_t	pid;
	int		status;

	if (hookup_pipes(idx_cmd, fd_pipe))
		exit(FD_DUP_ERROR);
	close_fd_table(nums_cmd, fd_pipe, idx_cmd);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		create_exe_proc(idx_cmd, fd_pipe);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		exit(PROCESS_ERROR);
	exit(EXIT_SUCCESS);
}

int	create_procs(int **fd_pipe)
{
	pid_t	*pids;
	int		idx_cmd;
	int		status;

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
			create_cmd_proc(idx_cmd, fd_pipe);
	}
	close_fd_table(nums_cmd, fd_pipe, -1);
	idx_cmd = -1;
	while (++idx_cmd < nums_cmd)
	{
		waitpid(pids[idx_cmd], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
			return (PROCESS_ERROR);
	}
	return (0);
}

int	build_pipeline(void)
{
	int	result;
	int	**fd_pipe;

	result = 0;
	fd_pipe = malloc_fd_table(nums_cmd);
	if (fd_pipe == NULL)
		error(MALLOC_FAILURE);
	if (fill_fd_table(nums_cmd, fd_pipe))
		error(PIPE_FAILURE);
	if (create_procs(fd_pipe))
		return (PROCESS_ERROR);
	free_fd_table(fd_pipe);
	return (result);
}
