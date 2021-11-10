#ifndef COMMAND_H
# define COMMAND_H

# include "common.h"

# define END 1

void	free_str(char **str);
int		token_size(char **token);
t_error	run_cd(t_list *args);
t_error	get_pwd(void);
void	print_export_list(t_list *export_list);
char	*make_str(t_list *export_list);
void	add_to_list(char *token, int num);
t_error	run_export(t_list *args);
t_error	run_unset(t_list *args, t_list **export_list, t_list **env_list);
void	get_env(t_list *envp);

void	malloc_error(void);

#endif
