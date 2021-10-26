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
#include "lib/libft.h"

#define SUCCESS			0
#define MALLOC_ERROR	1
#define TERMIOS_ERROR	1
#define RL_ERROR		1
#define PARSE_ERROR		1
#define SIGNAL_ERROR	1
#define EXEC_ERROR		1

/* typedef enum e_error
{
	SUCCESS = 0,
	MALLOC_ERROR,
	RL_ERROR
}	t_error; */

#define CUR_NONE		0
#define CUR_PIPE		1
#define CUR_REDIRECT	2
#define CUR_QUOTE		4
#define CUR_DQUOTE		8
#define CUR_CMD			16
#define CUR_PATH		32
#define CUR_ARG			64

typedef struct s_minishell
{
	t_list			*envp;
	int				signal;
	int				pid;
	int				eof;
	int				read_fd;
	char			*line;
}	t_minishell;

extern t_minishell	g_shell;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_token
{
	int		type;
	char	*value;
}					t_token;

typedef struct		s_lexer
{
	char		*line;
	t_list		*tokens;
	int			start;
	int			end;
}					t_lexer;

typedef struct		s_AST_Node
{
	int		type;
	void	*data;
}					t_AST_Node;
//t_list 를 ASTree로

typedef struct		s_cmd
{
	char	*cmd;
	t_list	*args;
}					t_cmd;

typedef struct		s_pipe
{
	t_AST_Node	*leftchild; // redirect or cmd
	t_AST_Node	*rightchild; // pipe or rediret or cmd
}					t_pipe;

typedef struct s_redirect
{
	int			type;
	t_AST_Node	*child;
	char		*file;
}	t_redirect;


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

