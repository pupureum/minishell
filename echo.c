#include "command.h"

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

int	run_echo(char **token)
{
	char	**str;
	int		i;
	int		j;
	int		len;

	len = token_size(token);
	str = (char **)malloc(sizeof(char *) * len);
	if (str == NULL)
		return (MALLOC_ERROR);
	i = 1;
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
	printf("exec 함수를 실행한 뒤는 메모리에서 사라짐\n");
	free_str(str);
	return (EXECVE_ERROR);
}

int	main(void)
{
	char	*arr[] = {"echo","-n", "hello", "hi", "kkk", ":)", NULL};

	run_echo(arr);
	return (0);
}
