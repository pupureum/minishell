#include "minishell.h"

t_error	run_cd(t_list *args)
{
	char	*path;
	int		result;

	if (args == NULL)
	{
		path = get_env_str("HOME");
		result = chdir(path);
		free(path);
	}
	else
		result = chdir((char *)args->content);
	if (result == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", args->content);
		return (PATH_OPEN_ERROR);
	}
	return (SUCCESS);
}
