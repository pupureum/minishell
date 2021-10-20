#include "command.h"

void	free_str(int **str)
{
	while (!(*str))
		free((*str)++);
	free (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;

	i = 0;
	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (uc_s1[i] != uc_s2[i] || uc_s1[i] == 0 || uc_s2[i] == 0)
			return (uc_s1[i] - uc_s2[i]);
		i++;
	}
	return (0);
}

int idenfify_commands(t_token *token, char **envp)
{
    if (ft_strncmp(token->value, "pwd", 4) == 0)
	{
        if (get_pwd() == (MALLOC_ERROR || EXECVE_ERROR))
		{
			printf("Echo Error");
			return (0);
		}
	}
    else if(ft_strncmp(token->value, "env", 4) == 0)
        get_env(envp);
    else if(ft_strncmp(token->value, "echo", 5) == 0)
	{
        if (run_echo(token) == (MALLOC_ERROR || EXECVE_ERROR))
		{
			printf("Echo Error");
			return (0);
		}
	}

//    else if(ft_strncmp(token->value, "echo", 5) == 0)
    else
    {
        printf("Error : Invalid command");
        return (0);
    }
    
}