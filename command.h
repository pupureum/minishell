#ifndef COMMAND_H
# define COMMAND_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

# define MALLOC_ERROR -1
# define EXECVE_ERROR -2
# define PATH_FAIL -3
# define INVALID_PATH -4

void	get_env(char **envp);
int	get_pwd(void);
int	run_echo(char **token);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

typedef struct	s_token
{
	int		type;
	char	*value;
}				t_token;

#endif