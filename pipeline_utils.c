/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:54:22 by bylee             #+#    #+#             */
/*   Updated: 2021/10/27 20:03:55 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

void	free_fd_table(int nums_cmd, int **fd_pipe)
{
	int i;

	i = -1;
	while (fd_pipe[++i])
		free(fd_pipe[i]);
	free(fd_pipe);
}

void	close_fd_table(int nums_cmd, int **fd_pipe, int idx_cmd)
{
	int	i;

	i = -1;
	while (++i < nums_cmd - 1)
	{
		if (idx_cmd - 1 != i)
			close(fd_pipe[i][0]);
		if (idx_cmd != i)
			close(fd_pipe[i][1]);
	}
}

int	**malloc_fd_table(int nums_cmd)
{
	int	**fd_pipe;
	int	i;

	i = -1;
	fd_pipe = (int **)malloc(sizeof(int *) * nums_cmd);
	if (!fd_pipe)
		return (NULL);
	fd_pipe[nums_cmd] = NULL;
	while (++i < nums_cmd - 1)
	{
		fd_pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd_pipe[i])
		{
			free_fd_table(nums_cmd, fd_pipe);
			return (NULL);
		}
	}
	return (fd_pipe);
}

int	fill_fd_table(int nums_cmd, int **fd_pipe)
{
	int	i;

	i = -1;
	while (++i < nums_cmd - 1)
	{
		if (pipe(fd_pipe[i]))
		{
			free_fd_table(nums_cmd, fd_pipe);
			return (PIPE_FAILURE);
		}
	}
	return (0);
}
