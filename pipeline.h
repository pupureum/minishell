/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:55:43 by bylee             #+#    #+#             */
/*   Updated: 2021/10/28 12:24:11 by bylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>

# define SUCCESS 0
# define MALLOC_FAILURE 1
# define PIPE_FAILURE 2
# define PROCESS_ERROR 3
# define FORK_ERROR 4
# define FD_DUP_ERROR 5
typedef struct s_token
{
	int		type;
	char	*value;
}				t_token;

/*
pipeline.c
*/
int		build_pipeline(void);

/*
pipeline_utils.c
*/
void	error(int errno);
int		**malloc_fd_table(int nums_cmd);
int		fill_fd_table(int nums_cmd, int **fd_pipe);
void	close_fd_table(int nums_cmd, int **fd_pipe, int idx_cmd);
void	free_fd_table(int **fd_pipe);

#endif
