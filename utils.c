#include "command.h"

void	malloc_error(void)
{
	printf("Malloc Error\n");
	exit(0);
}

char *add_char(char const *s1, char c)
{
	int	len;
	char *result;
	char *str;

	if (!(s1))
		return (NULL);
	ft_strdup(s1);
	result = (char *)malloc(sizeof(char) * len + 1);
	str = (char *)malloc(sizeof(char) * 2);
	if (result == NULL || str == NULL)
	{
		printf("Malloc Error");
		exit(0);
	}
	str[0] = '=';
	len = ft_strlen(s1) + 1;
	ft_strlcpy(result, s1, len);
	ft_strlcat(result, str, len + 1);
	return (result);
}

void	free_str(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

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

t_list	*init_envp(char *export_list[])
{
	int		i;
	char	*cur_export_list;
	t_list	*new;
	t_list	*r;

	i = 0;
	r = NULL;
	while (export_list[i])
	{
		new = ft_lstnew(export_list[i]);
		if (new == NULL)
		{
			printf("Malloc Error\n");
			exit(0);
		}
		if (r == NULL)
			r = new;
		else
			ft_lstadd_back(&r, new);
		i++;
	}
	return (r);
}