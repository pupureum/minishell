/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:07 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/20 15:03:04 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_H
# define TEMP_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef enum e_error
{
	SUCCESS = 0
}	t_error;

typedef struct s_token
{
	int		type;
	char	*value;
}	t_token;

typedef struct s_fd
{
	int		fd_shell;
	int		fd_proc;
}	t_fd;

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
