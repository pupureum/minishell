#include "command.h"

int run_cd(char **path)
{

    path = getcwd(NULL, 0);
	if (!path)
		return (PATH_FAIL);
	free(path);
	if (chdir("../Baekjoon") == -1)
		return (INVALID_PATH);
	
}

int	main(void)
{
	char	**path = {"cd", "../Baekjoon"};
	
	run_cd(**path);
	return (0);
}
