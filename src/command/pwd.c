#include "command.h"

int	get_pwd(void)
{
	char	**str;

	str = (char **)malloc(sizeof(char *) * 2);
	if (str == NULL)
		return (MALLOC_ERROR);
	str[0] = "/bin/pwd";
	str[1] = NULL;
	execve(str[0], str, NULL);
	printf("PWD Error");
	free(str);
	return (1);
}
