#include "command.h"

void	free_str(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	token_size(char **token)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (token[i++])
		len++;
	return (len);
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

static	int do_fork(int flag, t_token *token)
{
    int pid;
    int result;
    pid = fork();
    if (!pid)
    {
        if (flag == PWD)
            result = get_pwd();
        else if (flag == ECHO)
            result = run_echo(token);
        if (result == 1)
        {
            printf("ECHO or PWD ERROR\n");
            return (1);
        }
		else if (result == MALLOC_ERROR)
		{
			printf("Malloc Error\n");
			exit(0);
		}
    }
    else if (pid < 0)
	{
        printf("Fork Error");
		return (1);
	}
	wait(NULL);
    return(0);
}

int idenfify_commands(t_token *token, char **envp, t_Ast_Node *node)
{
    int pid;
	int result;
	// ((t_cmd *)(node->data))->cmd
	// node->data->args

    if (ft_strncmp(token->value, "pwd", 4) == 0)
        result = do_fork(PWD, token);
    else if(ft_strncmp(token->value, "env", 4) == 0)
        get_env(envp);
    else if(ft_strncmp(token->value, "echo", 5) == 0)
        result = do_fork(ECHO, token);
    else if(ft_strncmp(token->value, "cd", 3) == 0)
        result = run_cd(token);
    else if (ft_strncmp(token->value, "export", 7) == 0)
        result = run_export(token);
	else if (ft_strncmp(token->value, "unset", 6) == 0)
		result = run_unset(token);
    else
    {
        printf("Error : Invalid command");
        return (1);
    }
	if (result == 1)
		return (1);
	return (0);
}