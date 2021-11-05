#include "minishell.h"

t_error	get_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		error(MALLOC_ERROR);
	printf("%s\n", path);
	free(path);
	path = NULL;
	return (SUCCESS);
}
