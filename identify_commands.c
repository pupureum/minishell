#include "command.h"

static	int do_fork(int flag, char *token)
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

int idenfify_commands(char **envp, t_AST_Node *node)
{
    int pid;
	int result;
	// (((t_cmd *)(node->content))->cmd
	// node->data->args

    if (ft_strncmp(((t_cmd *)(node->content))->cmd, "pwd", 4) == 0)
        result = do_fork(PWD, ((char *)(((t_cmd *)(node->content))->args->content)));
    else if(ft_strncmp(((t_cmd *)(node->content))->cmd, "env", 4) == 0)
        get_env(envp);
    else if(ft_strncmp(((t_cmd *)(node->content))->cmd, "echo", 5) == 0)
        result = do_fork(ECHO, token);
    else if(ft_strncmp(((t_cmd *)(node->content))->cmd, "cd", 3) == 0)
        result = run_cd(token);
    else if (ft_strncmp(((t_cmd *)(node->content))->cmd, "export", 7) == 0)
        result = run_export(token);
	else if (ft_strncmp(((t_cmd *)(node->content))->cmd, "unset", 6) == 0)
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