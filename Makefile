# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 20:30:41 by bylee             #+#    #+#              #
#    Updated: 2021/11/13 01:50:22 by jihoolee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	gcc
# CFLAGS				=	-Wall -Wextra -Werror
RM					=	rm -f

LIBFT_DIR			=	lib/libft/
LIBFT_FLAG			= 	-lft

READLINE_INC_DIR	=	./lib/readline/include/
READLINE_LIB_DIR	=	./lib/readline/lib/
READLINE_FLAG		=	-lreadline

INCLUDE_DIR			=	./include

INTER_SRC_DIR		=	./src/interpreter/
INTER_SRCS			=	destruct_AST.c\
						interpreter.c\
						lexer_get_item.c\
						lexer.c\
						parse_cmd.c\
						parse_get_node.c\
						parse_type_check.c\
						parser.c\
						util.c\
						translate_dollar.c\
						translate_env.c\
						translate_home.c
INTER_OBJS			=	$(addprefix $(INTER_SRC_DIR), $(INTER_SRCS:.c=.o))

PIPE_SRC_DIR		=	./src/pipeline/
PIPE_SRCS			=	pipeline_utils.c\
						pipeline.c
PIPE_OBJS			=	$(addprefix $(PIPE_SRC_DIR), $(PIPE_SRCS:.c=.o))

REDIR_SRC_DIR		=	./src/redirection/
REDIR_SRCS			=	fd_new.c\
						format_filename.c\
						handle_redir.c\
						init_fd_table.c\
						redirect.c\
						search_proc_fd.c
REDIR_OBJS			=	$(addprefix $(REDIR_SRC_DIR), $(REDIR_SRCS:.c=.o))

COMMAND_SRC_DIR		=	./src/command/
COMMAND_SRCS		=	cd.c\
						env.c\
						export.c\
						pwd.c\
						unset.c\
						utils.c
COMMAND_OBJS		=	$(addprefix $(COMMAND_SRC_DIR), $(COMMAND_SRCS:.c=.o))

SRC_DIR				=	src/
SRCS				=	error.c\
						execute_cmd.c\
						init_envp.c\
						init_term.c\
						minishell.c\
						print_JSON.c\
						redir_and_exe.c\
						sort_export_list.c
OBJS				=	$(addprefix $(SRC_DIR), $(SRCS:.c=.o))

.c.o :
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -I $(READLINE_INC_DIR) -I $(LIBFT_DIR) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJS) $(INTER_OBJS) $(PIPE_OBJS) $(REDIR_OBJS) $(COMMAND_OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) -L $(LIBFT_DIR) -L $(READLINE_LIB_DIR) $(LIBFT_FLAG) $(READLINE_FLAG) $^
	install_name_tool -change /Users/bylee/.brew/opt/readline/lib/libreadline.8.dylib ./lib/readline/lib/libreadline.8.dylib minishell

all : $(NAME)

clean :
	$(RM) $(OBJS) $(INTER_OBJS) $(PIPE_OBJS) $(REDIR_OBJS) $(COMMAND_OBJS)
	make clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re : fclean all

test : $(OBJS) $(INTER_OBJS) $(PIPE_OBJS) $(REDIR_OBJS) $(COMMAND_OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -g3 -fsanitize=address -o $(NAME) -L $(LIBFT_DIR) -L $(READLINE_LIB_DIR) $(LIBFT_FLAG) $(READLINE_FLAG) $^
	install_name_tool -change /Users/bylee/.brew/opt/readline/lib/libreadline.8.dylib ./lib/readline/lib/libreadline.8.dylib minishell

.PHONY : all clean fclean re test
