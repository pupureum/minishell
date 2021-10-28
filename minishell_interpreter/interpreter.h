#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <errno.h>
#include "lib/libft/libft.h"

#define MALLOC_ERROR	1
#define PARSE_ERROR		1
#define SYMANTIC_ERROR	1
#define EXEC_ERROR		1

#define CUR_NONE		0
#define CUR_PIPE		1
#define CUR_REDIRECT	2
#define CUR_AFTER_FD	4
#define CUR_CMD			8
#define CUR_ARG			16
#define CUR_QUOTE		32
#define CUR_DQUOTE		64

#define TYPE_PIPE 		 	0
#define TYPE_REDIRECT		1
#define	TYPE_CMD 			2
#define	TYPE_ARG  			4
#define	TYPE_REDIR_STDIN	8
#define	TYPE_REDIR_STDOUT	16
#define	TYPE_REDIR_HEREDOC	32
#define	TYPE_REDIR_APPEND	64

#define END_COLOR "\033[0m"
#define KEY_COLOR "\033[1;35m"
#define VALUE_COLOR "\033[0;32m"

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
	void	*content;
}					t_AST_Node;

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
	char		*after_fd;
}	t_redirect;


t_AST_Node		*interpreter(char *line);
t_list			*lexical_analyzer(char *line);
char			*get_special_item(char **line, int *cur_option);
char			*get_plain_item(char **line);
t_AST_Node		*syntax_analyzer(t_list *token);
int				type_argument(t_cmd *cmd, t_list **arg, t_token *token);
int				type_redirect(t_AST_Node **curr, t_list **token);
t_AST_Node		*parse_cmd(t_list **token);
t_AST_Node		*parse_get_node(t_list **token);

void			malloc_error_check(void *item);
int				ft_malloc(void **dst, size_t size);

void 			print_series_token(t_list *token);
void			print_JSON(t_AST_Node	*AST, int indent);
void			print_indent(int indent);
