/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:09:04 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/19 17:26:58 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temp.h"

t_fd	*fd_lstnew(int shell_fd, int proc_fd)
{
	t_fd	*elem;

	elem = (t_fd *)malloc(sizeof(t_fd));
	if (elem == NULL)
		return (NULL);
	elem->shell_fd = shell_fd;
	elem->proc_fd = proc_fd;
	elem->next = NULL;
	return (elem);
}

int	fd_lstsize(t_fd *fd_lst)
{
	int	len;

	len = 0;
	while (fd_lst)
	{
		len++;
		fd_lst = fd_lst->next;
	}
	return (len);
}

t_fd	*fd_lstlast(t_fd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	fd_lstadd_back(t_fd **lst, t_fd *new)
{
	t_fd	*curr;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		curr = ft_lstlast(*lst);
		curr->next = new;
	}
}

void	fd_lstclear(t_fd **lst)
{
	t_fd	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}
}
