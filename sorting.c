#include "command.h"

int	get_short_len(char *s1, char *s2)
{
	if (ft_strlen(s1) < ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}

void	sorting(t_list **export_list)
{
	t_list	*cur;
	t_list	*cur2;
	t_list	*temp;
	int		list_len;
	int		i;

	cur = *export_list;
	while (cur)
	{
		cur2 = *export_list;
		i = -1;
		while (++i < ft_lstsize(*export_list) - 1)
		{
			if (ft_strncmp((char *)(cur2->content)
				, (char *)(cur2->next->content), get_short_len
				((char *)(cur2->content), (char *)(cur2->next->content))) > 0)
			{
				temp = cur2->content;
				cur2->content = cur2->next->content;
				cur2->next->content = temp;
			}
			cur2 = cur2->next;
		}
		cur = cur->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_list	*export_list;
	(void)ac;
	(void)av;

	export_list = init_envp(envp);
	get_env(export_list);
	sorting(&export_list);
	printf("-------------------------------------\n");
	get_env(export_list);
	// while(1){};
	return (0);
}

// ft_strncmp (s1, s2)   -> 올바르게 정렬됨 : 음수, 스위치 해야하면 양수