/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_proc_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:49:01 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/01 21:58:30 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

int	search_proc_fd(t_list *fd_table, int shell_fd)
{
	t_list	*curr;

	curr = fd_table;
	while (curr)
	{
		if (((t_fd *)curr->content)->fd_shell == shell_fd)
			return (((t_fd *)curr->content)->fd_proc);
		curr = curr->next;
	}
	return (INVALID_FD);
}
