#include "command.h"

int	run_echo(t_list *args)
{
	char	**str;
	int		i;
	int		len;

	len = ft_lstsize(args);
	str = (char **)malloc(sizeof(char *) * len);
	if (str == NULL)
		malloc_error();
	str[0] = "/bin/echo";
	i = 1;
	while (i <= len)
	{
		str[i] = args->content;
		i++;
		args = args->next;
	}
	str[i] = NULL;
	execve(str[0], str, NULL);
	free_str(str);
	printf("Echo exec Error\n");
	return (1);
}

// int	main(void)
// {
// 	t_list	*args;
// 	t_list	*new;

// 	args = ft_lstnew("abc");
// 	new = ft_lstnew("/Users/plee");
// 	if (args == NULL || new == NULL)
// 		return (0);
// 	ft_lstadd_back(&args, new);
// 	run_echo(args);
// 	return (0);
// }
