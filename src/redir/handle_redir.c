/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:34 by jihoolee          #+#    #+#             */
/*   Updated: 2021/10/28 21:12:25 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static int	open_after_fd(t_list *fd_table, t_redirect *redir)
{
	int	fd;

	if ((redir->after_fd)[0] == '&')
		fd = find_fd();
}

static int	parse_before_fd(int cmd_idx, char *line, t_redirect *redir)
{
	int		iter;
	char	redir_sign;
	int		fd;

	if (redir->type == TYPE_REDIR_APPEND || redir->type == TYPE_REDIR_STDOUT)
		redir_sign = '>';
	else
		redir_sign = '<';
	iter = -1;
	fd = 0;
	line = ft_strchr(line, redir_sign) - 1;
	while (ft_isdigit(*line))
	{
		fd = fd * 10 + (*line - '0');
		line--;
	}
	if (*line == ' ')
		return (fd);
	return (-1);
}

t_error	handle_redir(
		int cmd_idx, char **line, t_list **fd_table, t_redirect *redir)
{
	int	from_fd;
	int	proc_fd;

	from_fd = parse_before_fd(cmd_idx, *line, redir);
	if (from_fd == -1)
	{
		if (redir->type == TYPE_REDIR_STDOUT
			|| redir->type == TYPE_REDIR_APPEND)
			from_fd = 1;
		else
			from_fd = 0;
	}
	proc_fd = open_after_fd(*fd_table, redir);
}
