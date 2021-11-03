/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:59:31 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/03 21:00:35 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

#include "common.h"

/*
pipeline.c
*/
int		build_pipeline(t_AST_Node *node, int nums_cmd);

/*
pipeline_utils.c
*/
void	error_exit(int error_code);
int		hookup_pipes(int idx_cmd, int **fd_pipe, int nums_cmd);
int		**malloc_fd_table(int nums_cmd);
int		fill_fd_table(int nums_cmd, int **fd_pipe);
void	close_fd_table(int nums_cmd, int **fd_pipe, int idx_cmd);
void	free_fd_table(int **fd_pipe);

#endif
