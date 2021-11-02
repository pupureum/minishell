/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:09 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/28 14:00:20 by jihoolee         ###   ########.fr       */
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
	int				old_fd;
	int				new_fd;
}	t_redir;

/*
redir_new.c
*/
t_redir	*redir_new(t_redir_type type, int old_fd, int new_fd);

/*
error.c
*/
void	error(t_error error_code);

#endif