#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	get_pwd(void)
{
	char	**str;

	str = (char **)malloc(sizeof(char *) * 2);
	str[0] = "/bin/pwd";
	str[1] = NULL;
	execve(str[0], str, NULL);
	printf("Error");
}
