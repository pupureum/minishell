/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:59:10 by bylee             #+#    #+#             */
/*   Updated: 2021/10/20 16:24:47 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
int	nums_cmd = 2;

void	create_exe_proc(int idx_cmd, int **fd_pipe)
{
	dprintf(STDOUT_FILENO, "This is exe layer, cmd : %d\n", idx_cmd);
	exit(EXIT_SUCCESS);
}

void	create_cmd_proc(int idx_cmd, int **fd_pipe)
{
	pid_t	pid;
	
	pid = fork();
	if (!pid)
		create_exe_proc(idx_cmd, fd_pipe);
	else
	{
		dprintf(STDOUT_FILENO, "This is cmd layer, cmd : %d\n", idx_cmd);
		exit(EXIT_SUCCESS);
	}
}

int	create_procs(int **fd_pipe)
{
	pid_t	*pid_cmd_proc;
	int		idx_cmd;

	idx_cmd = -1;
	pid_cmd_proc = (pid_t *)malloc(sizeof(pid_t) * nums_cmd);
	if (!pid_cmd_proc)
		return (MALLOC_FAILURE);
	while (++idx_cmd < nums_cmd)
	{
		pid_cmd_proc[idx_cmd] = fork();
		if (pid_cmd_proc[idx_cmd] == -1)
			return (PROCESS_ERROR);
		else if (!pid_cmd_proc[idx_cmd])
			create_cmd_proc(idx_cmd, fd_pipe);
	}
	// idx_cmd = -1;
	// while (++idx_cmd < nums_cmd)
	// 	waitpid();
	return (0);
}

int	build_pipeline(void)
{
	int result;
	int	**fd_pipe;

	result = 0;
	fd_pipe = malloc_fd_table(nums_cmd);
	if (!fd_pipe)
		return (MALLOC_FAILURE);
	if (fill_fd_table(nums_cmd, fd_pipe))
		return (PIPE_FAILURE);
	if (create_procs(fd_pipe))
		return (PROCESS_ERROR);
	close_fd_table(nums_cmd, fd_pipe);
	free_fd_table(fd_pipe);
	return (result);
}