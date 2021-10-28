// #include "command.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)(s + i));
// 		i++;
// 	}
// 	if (s[i] == (char)c)
// 		return ((char *)(s + i));
// 	return (NULL);
// }

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t i;

// 	i = 0;
// 	if (dst == 0 || src == 0)
// 		return (0);
// 	if (dstsize > 0)
// 	{
// 		while (src[i] && i < (dstsize - 1))
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = 0;
// 	}
// 	return (ft_strlen(src));
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t i;

// 	if (n == 0)
// 		return (0);
// 	i = 0;
// 	while (s1[i] == s2[i] && s1[i] != '\0')
// 	{
// 		if (i < (n - 1))
// 			i++;
// 		else
// 			return (0);
// 	}
// 	return ((unsigned char)s1[i] - (unsigned char)(s2[i]));
// }

// t_list	*ft_lstlast(t_list *lst)
// {
// 	if (lst == 0)
// 		return (0);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*curr;

// 	if (lst == 0 || new == 0)
// 		return ;
// 	if (*lst == 0)
// 		*lst = new;
// 	else
// 	{
// 		curr = ft_lstlast(*lst);
// 		curr->next = new;
// 	}
// }

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*element;

// 	element = (t_list *)malloc(sizeof(t_list));
// 	if (!element)
// 		return (0);
// 	element->content = content;
// 	element->next = 0;
// 	return (element);
// }

// int ft_lstsize(t_list *lst)
// {
//     int n;
//     n = 0;
//     while (lst)
//     {
//         lst = lst->next;
//         n++;
//     }
//     return (n);
// }

// static	int	word_count(char const *s, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			count++;
// 			while (*s && *s != c)
// 				s++;
// 		}
// 		else
// 			s++;
// 	}
// 	return (count);
// }

// static	void	memfree(char **s, int index)
// {
// 	int	i;

// 	i = 0;
// 	while (i < index)
// 	{
// 		free(s[i]);
// 		i++;
// 	}
// 	free(s);
// }

// static	void	get_word_len(size_t *word_len, const char *s, char c)
// {
// 	if (ft_strchr(s, c) == NULL)
// 		*word_len = ft_strchr(s, '\0') - s;
// 	else
// 		*word_len = ft_strchr(s, c) - s;
// }

// static	int	word_get(char **ans, int wordcount, char const *s, char c)
// {
// 	char	*word;
// 	int		index;
// 	size_t	word_len;

// 	index = 0;
// 	while (index < wordcount)
// 	{
// 		while (*s == c)
// 			s++;
// 		get_word_len(&word_len, s, c);
// 		word = (char *)malloc(word_len + 1);
// 		if (word == NULL)
// 		{
// 			memfree(ans, index);
// 			return (-1);
// 		}
// 		ft_strlcpy(word, s, word_len + 1);
// 		ans[index] = word;
// 		s = s + word_len;
// 		index++;
// 	}
// 	ans[index] = 0;
// 	return (0);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		wordcount;
// 	char	**ans;

// 	if (s == 0)
// 		return (0);
// 	wordcount = word_count(s, c);
// 	ans = (char **)malloc(sizeof(char *) * (wordcount + 1));
// 	if (ans == NULL)
// 		return (0);
// 	if (word_get(ans, wordcount, s, c) == -1)
// 		return (0);
// 	return (ans);
// }

// char	*ft_strdup(const char *s1)
// {
// 	char	*ans;
// 	size_t	len;

// 	len = ft_strlen(s1);
// 	ans = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!ans)
// 		return (0);
// 	ft_strlcpy(ans, s1, len + 1);
// 	return (ans);
// }