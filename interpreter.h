#ifndef _INTERPRETER_H
# define _INTERPRETER_H

#pragma once
#include "minishell.h"


t_AST_Node		*interpreter(char *line);
t_list			*lexical_analyzer(char *line);
char			*get_special_item(char **line, int *cur_option);
char			*get_plain_item(char **line);
t_AST_Node		*syntax_analyzer(t_list *token);
int				type_argument(t_cmd *cmd, t_list **arg, t_token *token);
int				type_redirect(t_AST_Node **curr, t_list **token);
t_AST_Node		*parse_cmd(t_list **token);
t_AST_Node		*parse_get_node(t_list **token);

void			malloc_error_check(void *item);
int				ft_malloc(void **dst, size_t size);

void 			print_series_token(t_list *token);
void			print_JSON(t_AST_Node	*AST, int indent);
void			print_indent(int indent);

#endif