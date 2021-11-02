/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:09:04 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/01 21:48:20 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temp.h"

t_fd	*fd_new(int fd_shell, int fd_proc)
{
	t_fd	*new;

	new = (t_fd *)malloc(sizeof(t_fd));
	if (new == NULL)
		return (NULL);
	new->fd_shell = fd_shell;
	new->fd_proc = fd_proc;
	return (new);
}
