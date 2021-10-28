/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylee <bylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:55:43 by bylee             #+#    #+#             */
/*   Updated: 2021/10/28 19:11:51 by bylee            ###   ########.fr       */
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

# define TYPE_PIPE 0
# define TYPE_REDIRECT 1
# define TYPE_CMD 2

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_AST_Node
{
	int		type;
	void	*content;
}	t_AST_Node;

typedef struct s_cmd
{
	char	*cmd;
	t_list	*args;
}	t_cmd;

typedef struct s_pipe
{
	t_AST_Node	*leftchild;
	t_AST_Node	*rightchild;
}	t_pipe;

typedef struct s_redirect
{
	int			type;
	t_AST_Node	*child;
	char		*after_fd;
}	t_redirect;

/*
pipeline.c
*/
int		build_pipeline(t_AST_Node *node, int nums_cmd);

/*
pipeline_utils.c
*/
void	error(int errno);
int		hookup_pipes(int idx_cmd, int **fd_pipe, int nums_cmd);
int		**malloc_fd_table(int nums_cmd);
int		fill_fd_table(int nums_cmd, int **fd_pipe);
void	close_fd_table(int nums_cmd, int **fd_pipe, int idx_cmd);
void	free_fd_table(int **fd_pipe);

#endif
