/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:55:43 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/22 13:41:52 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_redir	*redir_new(t_redir_type type, int old_fd, int new_fd)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->old_fd = old_fd;
	new->new_fd = new_fd;
	return (new);
}
