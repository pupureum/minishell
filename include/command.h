#ifndef COMMAND_H
# define COMMAND_H

# include "common.h"

# define END 1

void	free_str(char **str);
int		token_size(char **token);
int		run_cd(t_list *args);
int		get_pwd();
void	print_export_list();
char	*make_str(t_list *export_list);
void	add_to_list(char *token, int num);
int		run_export(t_list *args);
int		run_unset(t_list *args, t_list **export_list, t_list **env_list);
int		get_env();

void	malloc_error(void);

#endif
