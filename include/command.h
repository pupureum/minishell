#ifndef COMMAND_H
# define COMMAND_H

# include "common.h"
# include "interpreter.h"

# define END 1

void	free_str(char **str);
int		token_size(char **token);
int		run_cd(t_list *args, t_list *fd_table);
int		get_pwd(t_list *fd_table);
void	print_export_list(t_list *export_list);
char	*make_str(t_list *export_list);
void	add_to_list(char *token, int num);
t_error	run_export(t_list *args);
t_error	run_unset(t_list *args, t_list **export_list, t_list **env_list);
void	get_env(t_list *envp);
int		ft_exit(t_list *args, t_list *fd_table);
void	malloc_error(void);
void	run_execve(t_cmd *cmd);

#endif
