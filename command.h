#ifndef COMMAND_H
# define COMMAND_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

# define MALLOC_ERROR -1
# define EXECVE_ERROR -2
# define PATH_FAIL -3
# define INVALID_PATH -4
# define ECHO 1
# define PWD 2
# define END 3

typedef struct		s_minishell
{
	t_list			*export_list;
	t_list			*env_list;
	char			*line;
	int				cmd_cnt;
	char			*exit_status;
}					t_minishell;

t_minishell g_shell;

typedef struct	s_token
{
	int		type;
	char	*value;
}				t_token;

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

// typedef struct s_list
// {
// 	void	*content;
// 	struct s_list	*next;
// }			t_list;

void	free_str(char **str);
int	token_size(char **token);
t_list	*init_envp(char *export_list[]);
int	get_pwd(void);
int	run_echo(t_list *args);
void	print_export_list(t_list *export_list);
char	*make_str(t_list *export_list);
void	add_to_list(char *token, t_list *export_list);
int	run_export(t_list *args, t_list *export_list, t_list *env_list);
int	run_unset(t_list *args, t_list **export_list, t_list **env_list);
void	get_env(t_list *envp);

void	malloc_error(void);

#endif