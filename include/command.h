#ifndef COMMAND_H
# define COMMAND_H

# include "common.h"

# define END 1

void	free_str(char **str);
int		token_size(char **token);
int		run_cd(t_list *args);
int		get_pwd();
char	*make_str(t_list *export_list);
void	print_export_list();
void	add_to_list(char *token, t_list **list);
int		run_export(t_list *args);
int		check_dup(t_list *list, char *arg);
int		run_unset(t_list *args);
int		get_env();

void	malloc_error(void);

#endif
