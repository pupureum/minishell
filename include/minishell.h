#ifndef _MINISHELL_H
# define _MINISHELL_H

#pragma once

#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <termcap.h>
#include <errno.h>
#include "lib/libft/libft.h"

#define MALLOC_ERROR	1
#define PARSE_ERROR		1
#define SYMANTIC_ERROR	1
#define EXEC_ERROR		1

# define SUCCESS 0
# define MALLOC_FAILURE 1
# define PIPE_FAILURE 2
# define PROCESS_ERROR 3
# define FORK_ERROR 4
# define FD_DUP_ERROR 5

#define CUR_NONE		0
#define CUR_PIPE		1
#define CUR_REDIRECT	2
#define CUR_BEFORE_FD	4
#define CUR_AFTER_FD	8
#define CUR_CMD			16
#define CUR_ARG			32
#define CUR_QUOTE		64
#define CUR_DQUOTE		128

//#define CUR_BEFORE_FD type
//		-> is_num(int값 범위) + no_space, 이게 아니면 스페이스붙어있어도 arg로
// (파서) : 얘를 파서에서 위치를찾아야되고 -> < , > 메소드로 넣어줘야됨 
//

#define TYPE_PIPE 		 	0
#define TYPE_REDIRECT		1
#define	TYPE_CMD 			2
#define	TYPE_ARG  			4
#define	TYPE_REDIR_STDIN	8
#define	TYPE_REDIR_STDOUT	16 // 
#define	TYPE_REDIR_HEREDOC	32 // dafault 0 
#define	TYPE_REDIR_APPEND	64 // default 1

#define MALLOC_ERROR	1
#define TERMIOS_ERROR	1
#define RL_ERROR		1
#define PARSE_ERROR		1
#define SIGNAL_ERROR	1
#define EXEC_ERROR		1

#define END_COLOR "\033[0m"
#define KEY_COLOR "\033[1;35m"
#define VALUE_COLOR "\033[0;32m"

typedef struct		s_minishell
{
	t_list			*envp;
	char			*line;
	int				cmd_cnt;
	char			*exit_status;
}					t_minishell;

t_minishell g_shell;


typedef struct		s_token
{
	int		type;
	char	*value;
}					t_token;

typedef struct		s_AST_Node
{
	int		type;
	void	*content;
}					t_AST_Node;

typedef struct		s_cmd
{
	char	*cmd;
	t_list	*args;
}					t_cmd;

typedef struct		s_pipe
{
	int			count;
	t_AST_Node	*leftchild; // redirect or cmd
	t_AST_Node	*rightchild; // pipe or rediret or cmd
}					t_pipe;

typedef struct s_redirect
{
	int			type;
	t_AST_Node	*child;
	int			before_fd;
	char		*after_fd;
}	t_redirect;

void			execute(t_AST_Node *node);
int				init_envp(char *envp[]);
int				set_term_mode(struct termios *term);
int				get_term_mode(struct termios *term);
int				init_nonc_mode(struct termios *new);
int				init_term(struct termios *org, struct termios *new);

t_AST_Node		*interpreter(char *line);
t_list			*lexical_analyzer(char *line);
char			*get_special_item(char **line, int *cur_option);
char			*get_plain_item(char **line, int *cur_option);
t_AST_Node		*syntax_analyzer(t_list *token);
int				type_argument(t_cmd *cmd, t_list **arg, t_token *token);
int				type_redirect(t_AST_Node **curr, t_list **token);
t_AST_Node		*parse_cmd(t_list **token);
t_AST_Node		*parse_get_node(t_list **token);

void			malloc_error_check(void *item);
int				ft_malloc(void **dst, size_t size);
int 			check_invalid_fd(char *word);
int				set_quote_option(char **line, int *cur_option);

void 			print_series_token(t_list *token);
void			print_JSON(t_AST_Node	*AST, int indent);
void			print_indent(int indent);

int		symantic_analyzer(t_AST_Node *node);
/*
pipeline.c
*/
int		build_pipeline(t_AST_Node *node, int nums_cmd);

/*
pipeline_utils.c
*/
void	error_exit(int error_code);
int		hookup_pipes(int idx_cmd, int **fd_pipe, int nums_cmd);
int		**malloc_fd_table(int nums_cmd);
int		fill_fd_table(int nums_cmd, int **fd_pipe);
void	close_fd_table(int nums_cmd, int **fd_pipe, int idx_cmd);
void	free_fd_table(int **fd_pipe);


/*
----------------------------- redir ---------------------
*/
#define CHMOD644			S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH

#define INVALID_FD		-1

#define HEREDOC_ERROR	1
#define FILE_OPEN_ERROR	1

typedef struct s_fd
{
	// int	type;
	int	fd_shell;
	int	fd_proc;
}	t_fd;

t_fd	*fd_new(int fd_shell, int fd_proc);
int		search_proc_fd(t_list *fd_table, int shell_fd);
void	error(t_error error_code);
t_error	handle_redir(int idx_cmd, t_list **fd_table, t_redirect *redir);

t_list	*init_fd_table(void);

#endif

/*
char * ->
t_pipe->leftchild ->

if t_AST_NODE->TYPE = t_pipe
{
	destructor_pipe(t_AST_NODE);
}

if
ft_lstclear(AST, destructor_pipe)

destrucor {
	if t_AST_NODE->TYPE = t_pipe
{
	destructor_pipe(t_AST_NODE);
}
}

*/

