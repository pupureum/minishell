#include "minishell.h"

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
		printf("token num : %d, token_type: %d, token_value: %s\n", count, ((t_token *)temp->content)->type, ((t_token *)temp->content)->value);
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

int check_invalid_fd(char *word)
{
	char *ptr;
	int  num;

	ptr = word;
	while (*ptr)
	{
		if (!ft_isdigit(*ptr))
		{
			return (0);	
		}
		ptr++;
	}
	ptr = word;
	num = ft_atoi(ptr);

	if (num <= 255 && num >=0)
		return (1);

	return (0);
}

int	set_quote_option(char **line, int *temp_option, int *cur_option)
{
	if (!ft_strncmp("'", *line, 1) && !(*temp_option & CUR_DQUOTE))
	{
		if (*temp_option & CUR_QUOTE)
		{
			*temp_option ^= CUR_QUOTE;
			*cur_option |= CUR_QUOTE;
		}
		else
			*temp_option |= CUR_QUOTE;
		return (1);
	}
	else if (!ft_strncmp("\"", *line, 1) && !(*temp_option & CUR_QUOTE))
	{
		if (*temp_option & CUR_DQUOTE)
		{
			*temp_option ^= CUR_DQUOTE;
			*cur_option |= CUR_DQUOTE;
		}
		else
			*temp_option |= CUR_DQUOTE;
		return (1);
	}
	return (0);
}


//0->1
// 1->0