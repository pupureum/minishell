#include "minishell.h"

int	init_envp(char *envp[])
{
	int		i;
	char	*cur_envp;
	t_list	*new;

	i = 0;
	while (envp[i])
	{
		cur_envp = ft_strdup(envp[i]);
		if (cur_envp == NULL)
			return (MALLOC_ERROR);
		new = ft_lstnew(cur_envp);
		if (new == NULL)
			return (MALLOC_ERROR);
		ft_lstadd_back(&(g_shell.envp), new);
		i++;
	}
	return (SUCCESS);
}

int	set_term_mode(struct termios *term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) == -1)
		return (TERMIOS_ERROR);
	return (SUCCESS);
}

int	get_term_mode(struct termios *term)
{
	if (tcgetattr(STDIN_FILENO, term) == -1)
		return (TERMIOS_ERROR);
	return (SUCCESS);
}

int	init_nonc_mode(struct termios *new)
{
	if (get_term_mode(new) == TERMIOS_ERROR)
		return (TERMIOS_ERROR);
	new->c_lflag &= ~(ICANON | ECHOCTL);
	new->c_cc[VMIN] = 1;
	new->c_cc[VTIME] = 0;

}


int	init_term(struct termios *org, struct termios *new)
{
	if (get_term_mode(org) == TERMIOS_ERROR)
		return (TERMIOS_ERROR);
	if (set_nonc_mode(new) == TERMIOS_ERROR)
		return (TERMIOS_ERROR);
	return (SUCCESS);
}
