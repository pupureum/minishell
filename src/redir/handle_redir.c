/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:34 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/01 19:31:57 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

char	*format_filename(int idx)
{
	char	*num_str;
	char	*filename;

	num_str = ft_itoa(idx);
	filename = ft_strjoin(".tempfile", num_str);
	free(num_str);
	return (filename);
}

int	open_heredoc(int idx_cmd, char *EOF_str)
{
	int		temp_fd;
	char	*filename;
	char	*line;

	filename = format_filename(idx_cmd);
	temp_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
	free(filename);
	if (temp_fd == -1)
		return (temp_fd);
	while (1)
	{
		line = readline("> ");
		if (line == NULL|| ft_strncmp(line, EOF_str, ft_strlen(EOF_str)) == 0)
			break ;
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
	return (temp_fd);
}

int	open_file(int idx_cmd, t_redirect *redir)
{
	int	fd;

	if (redir->type == TYPE_REDIR_HEREDOC)
		fd = open_heredoc(idx_cmd, redir->after_fd);
	else if (redir->type == TYPE_REDIR_STDIN)
		fd = open(redir->after_fd, O_RDONLY | O_TRUNC, CHMOD644);
	else if (redir->type == TYPE_REDIR_STDOUT)
		fd = open(redir->after_fd, O_WRONLY | O_CREAT | O_TRUNC, CHMOD644);
	else
		fd = open(redir->after_fd, O_WRONLY | O_CREAT | O_APPEND, CHMOD644);
	if (fd < 0)
	{
		if (redir->type == TYPE_REDIR_HEREDOC)
			error(HEREDOC_ERROR);
		else
			printf("bash: %s: No such file or directory.\n");
	}
	return (fd);
}

t_error	handle_redir(int idx_cmd, t_list **fd_table, t_redirect *redir)
{
	int	proc_fd;

	if (redir->after_fd[0] == '&')
		proc_fd = get_proc_fd(redir->after_fd + 1);
	else
		proc_fd = open_file(idx_cmd, redir);
	if (proc_fd < 0)
		return (FILE_OPEN_ERROR);
}
