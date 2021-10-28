#include "command.h"

int run_cd(char **token)
{
	int	i;
	char *path;

	i = 1;
	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	printf("Before:\t%s\n", path);
	if (chdir(token[1]) == -1)
	{
		printf("Invalid path\n");
		return (1);	
	}
	path = getcwd(NULL, 0);
	if (!path)
		return (PATH_FAIL);
	printf("After : %s\n", path);
	free(path);
	return (0);
}

int	main(void)
{
	char	*path[] = {"cd", "../Baekjoon"};
	
	run_cd(path);
	return (0);
}
