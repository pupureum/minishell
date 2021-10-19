/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:53:48 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/19 19:26:25 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_fd	*init_fd_table(void)
{
	t_fd	*fd_table;

	fd_table = fd_lstnew(0, STDIN_FILENO);
	fd_lstadd_back(&fd_table, fd_lstnew(1, STDOUT_FILENO));
	fd_lstadd_back(&fd_table, fd_lstnew(2, STDERR_FILENO));
	if (fd_lstsize(fd_table) != 3)
	{
		fd_lstclear(&fd_table);
		return (NULL);
	}
	return (fd_table);
}

int	main(void)
{
	t_fd	*fd_table;
	t_token	*tokens;

	fd_table = init_fd_table();
	if (fd_table == NULL)
		error();
	if (parse_redir(&fd_table, tokens) != SUCCESS)
		error();
	return (0);
}
