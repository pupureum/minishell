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

typedef struct	s_token
{
	int		type;
	char	*value;
}				t_token;

// typedef struct s_list
// {
// 	void	*content;
// 	struct s_list	*next;
// }			t_list;

void	get_env(t_list *envp);
void	free_str(char **str);
int	token_size(char **token);
int	get_pwd(void);
int	run_echo(char **token);

#endif