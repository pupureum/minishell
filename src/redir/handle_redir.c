/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:07:34 by jihoolee          #+#    #+#             */
/*   Updated: 2021/11/01 22:00:23 by jihoolee         ###   ########.fr       */
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
	if (temp_fd == INVALID_FD)
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

int	ft_itoa_fd(char *fd_char)
{
	int	fd;

	fd = 0;
	while (ft_isdigit(*fd_char))
	{
		fd = fd * 10 + (*fd_char - '0');
		fd_char++;
	}
	if (fd_char != '\0')
		return (INVALID_FD);
	return (fd);
}

int	get_proc_fd(t_list *fd_table, char *fd_char)
{
	int	shell_fd;
	int	proc_fd;

	shell_fd = ft_itoa_fd(fd_char);
	if (shell_fd == INVALID_FD)
	{
		printf("bash: %s: ambiguous redirect\n");
		return (INVALID_FD);
	}
	proc_fd = search_proc_fd(fd_table, shell_fd);
	if (proc_fd == INVALID_FD)
	{
		printf("bash: %s: Bad file descriptor\n");
		return (INVALID_FD);
	}
	return (proc_fd);
}

t_error	handle_redir(int idx_cmd, t_list **fd_table, t_redirect *redir)
{
	int	proc_fd;

	if (redir->after_fd[0] == '&')
		proc_fd = get_proc_fd(*fd_table, redir->after_fd + 1);
	else
		proc_fd = open_file(idx_cmd, redir);
	if (proc_fd < 0)
		return (FILE_OPEN_ERROR);
}
