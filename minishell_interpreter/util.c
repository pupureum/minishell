#include "interpreter.h"

void malloc_error_check(void *item)
{
    if (item == NULL)
    {
        printf("%s\n", strerror(12));
        exit(1);
    }
}

int	ft_malloc(void **dst, size_t size)
{
	*dst = ft_calloc(size, 1);
	if (*dst == NULL)
		return (0);
	return (1);
}

void print_series_token(t_list *token)
{
	t_list *temp;
	int count;

	temp = token;
	count = 0;
	while (temp)
	{
		printf("token num : %d, token_type: %d, token_value: %s\n", count, ((t_token *)(temp)->content)->type, ((t_token *)(temp)->content)->value);
		temp = temp->next;
		count++;
	}
}

void	print_indent(int indent)
{
	while (indent)
	{
		printf("\t");
		indent--;
	}
}