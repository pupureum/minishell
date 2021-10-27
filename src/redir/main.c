/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:53:48 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/23 16:51:22 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static int	is_fd_table_valid(t_list *fd_table, int len)
{
	int	count;

	count = 0;
	while (fd_table)
	{
		if (fd_table->content == NULL)
			return (0);
		count++;
		fd_table = fd_table->next;
	}
	if (count != len)
		return (0);
	return (1);
}

t_list	*init_fd_table(void)
{
	t_list	*fd_table;
	int		i;

	fd_table = ft_lstnew(fd_new(0, STDIN_FILENO));
	ft_lstadd_back(&fd_table, ft_lstnew(fd_new(1, STDOUT_FILENO)));
	ft_lstadd_back(&fd_table, ft_lstnew(fd_new(2, STDERR_FILENO)));
	if (is_fd_table_valid(fd_table, 3) == 0)
	{
		ft_lstclear(&fd_table, free);
		return (NULL);
	}
	return (fd_table);
}

int	main(void)
{
	t_list	*fd_table;
	t_token	**tokens;

	fd_table = init_fd_table();
	if (fd_table == NULL)
		error();
	if (handle_redir(&fd_table, tokens) != SUCCESS)
	{
		ft_lstclear(&fd_table, free);
		error();
	}
	return (0);
}
