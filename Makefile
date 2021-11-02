# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bylee <bylee@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 20:30:41 by bylee             #+#    #+#              #
#    Updated: 2021/11/02 21:37:58 by bylee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

LIBFT_DIR		=	lib/libft/
LIBFT_FLAG		= 	-lft

READLINE_INC	=	-I./lib/readline/include
READLINE_LIB	=	-L./lib/readline/lib
READLINE_FLAG	=	-lreadline

INCLUDE_DIR		=	./include

SRCS_DIR		=	./srcs
INTER_SRCS_DIR	=	$(addprefix $(SRCS_DIR)/, interpreter/)
PIPE_SRCS_DIR	=	$(addprefix $(SRCS_DIR)/, pipeline/)
REDIR_SRCS_DIR	=	$(addprefix $(SRCS_DIR)/, redirection/)

-lreadline -L/Users/bylee/.brew/opt/readline/lib -I/Users/bylee/.brew/opt/readline/include