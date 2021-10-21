/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:09 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/21 17:01:36 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "temp.h"

typedef enum e_redir_type
{
	INPUT = 1,
	OUTPUT,
	OUTPUT_APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	int				src_fd;
	int				dst_fd;
}	t_redir;

/*
redir_new.c
*/
t_redir	*redir_new(t_redir_type type, int src_fd, int dst_fd);

#endif
