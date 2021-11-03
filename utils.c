#include "command.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				n[2];
	unsigned char	u1;
	unsigned char	u2;

	n[0] = ft_strlen(s1);
	n[1] = ft_strlen(s2);
	if (n[0] != n[1])
		return (1);
	while (n[0]-- > 0)
	{
		u1 = *(unsigned char *)s1++;
		u2 = *(unsigned char *)s2++;
		if (u1 != u2)
			return (u1 - u2);
		if (u1 == '\0')
			return (0);
	}
	return (0);
}

void	malloc_error(void)
{
	printf("Malloc Error\n");
	exit(0);
}

void	add_to_list(char *token, t_list *export_list)
{
	t_list	*new;

	new = ft_lstnew(token);
	if (new == NULL)
	{
		printf("Malloc Error");
		exit(0);
	}
	ft_lstadd_back(&export_list, new);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
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
