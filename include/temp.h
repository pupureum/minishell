/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:07 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/28 19:04:02 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_H
# define TEMP_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define REDIRECT_LEFT	1
# define REDIRECT_RIGHT	2

#define TYPE_PIPE 		 	0
#define TYPE_REDIRECT		1
#define	TYPE_CMD 			2
#define	TYPE_ARG  			4
#define	TYPE_REDIR_STDIN	8
#define	TYPE_REDIR_STDOUT	16
#define	TYPE_REDIR_HEREDOC	32
#define	TYPE_REDIR_APPEND	64

typedef struct s_minishell
{
	t_list			*envp;
	int				signal;
	int				pid;
	int				eof;
	int				read_fd;
	char			*line;
}	t_minishell;

extern t_minishell	g_shell;

typedef enum e_error
{
	SUCCESS = 0,
	MALLOC_ERROR
}	t_error;

typedef struct s_fd
{
	int		fd_shell;
	int		fd_proc;
}	t_fd;

typedef struct s_token
{
	int		type;
	char	*value;
}	t_token;

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
	t_AST_Node	*leftchild; // redirect or cmd
	t_AST_Node	*rightchild; // pipe or rediret or cmd
}	t_pipe;

typedef struct s_redirect
{
	int			type;
	t_AST_Node	*child;
	char		*after_fd;
}	t_redirect;

/*
fd_new.c
*/
t_fd	*fd_new(int fd_shell, int fd_proc);

/* t_fd	*fd_lstnew(int fd_shell, int fd_proc);
int		fd_lstsize(t_fd *fd_lst);
t_fd	*fd_lstlast(t_fd *lst);
void	fd_lstadd_back(t_fd **lst, t_fd *new);
void	fd_lstclear(t_fd **lst); */

#endif
