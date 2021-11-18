#include "minishell.h"

void	open_heredoc(int idx_cmd, char *EOF_str)
{
	int		temp_fd;
	char	*filename;
	char	*line;

	filename = format_filename(idx_cmd);
	temp_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == INVALID_FD)
		error(FILE_OPEN_ERROR);
	while(1)
	{
		line = readline("> ");
		if (line == NULL \
			|| ft_strncmp(line, EOF_str, ft_strlen(EOF_str) + 1) == 0)
			break ;
		write(temp_fd, line, ft_strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(temp_fd);
	free(filename);
}

void	handle_heredoc(t_AST_Node *node, int idx_cmd)
{
	if (node == NULL)
		return ;
	if (node->type == TYPE_PIPE)
	{
		handle_heredoc(((t_pipe *)(node->content))->leftchild, idx_cmd);
		handle_heredoc(((t_pipe *)(node->content))->rightchild, idx_cmd + 1);
	}
	else if (node->type == TYPE_REDIRECT)
	{
		if (((t_redirect *)(node->content))->type == TYPE_REDIR_HEREDOC)
		{
			open_heredoc(idx_cmd, ((t_redirect *)(node->content))->after_fd);
			((t_redirect *)(node->content))->type = TYPE_REDIR_STDIN;
			free(((t_redirect *)(node->content))->after_fd);
			((t_redirect *)(node->content))->after_fd = format_filename(idx_cmd);
		}
		handle_heredoc(((t_redirect *)(node->content))->child, idx_cmd);
	}

}
