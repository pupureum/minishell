#include "command.h"

int	run_echo(char *token)
{
	char	**str;
	int		i;
	int		j;
	int		len;

	len = token_size(token);
	str = (char **)malloc(sizeof(char *) * len);
	if (str == NULL)
		malloc_error();
	i = 0;
	str[0] = "/bin/echo";
	j = 1;
	while (j <= len - 1)
	{
		str[j] = token[i];
		i++;
		j++;
	}
	str[j] = NULL;
	execve(str[0], str, NULL);
	free_str(str);
	printf("Echo exec Error\n");
	return (1);
}

int	main(void)
{
	char	*arr[] = {"echo","-n", "hello", "hi", "kkk", ":)", NULL};

	run_echo(arr);
	return (0);
}
