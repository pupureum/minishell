/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:54:22 by bylee             #+#    #+#             */
/*   Updated: 2021/10/21 17:02:38 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

void	free_fd_table(int **fd_pipe)
{
	while (!(*fd_pipe))
		free((*fd_pipe)++);
	free(fd_pipe);
}

void	close_fd_table(int nums_cmd, int **fd_pipe)
{
	int	i;

	i = 0;
	while (i < nums_cmd)
	{
		close(fd_pipe[i][0]);
		close(fd_pipe[i][1]);
		i++;
	}
}

int	**malloc_fd_table(int nums_cmd)
{
	int	**fd_pipe;
	int	i;

	i = 0;
	fd_pipe = (int **)malloc(sizeof(int *) * nums_cmd);
	if (!fd_pipe)
		return (NULL);
	while (i < nums_cmd)
	{
		fd_pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd_pipe[i])
		{
			free_fd_table(fd_pipe);
			return (NULL);
		}
		i++;
	}
	return (fd_pipe);
}

int	fill_fd_table(int nums_cmd, int **fd_pipe)
{
	int	i;

	i = 0;
	while (i < nums_cmd)
	{
		if (pipe(fd_pipe[i++]))
			return (PIPE_FAILURE);
	}
	return (0);
}
