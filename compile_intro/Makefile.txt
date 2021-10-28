
NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RLFLAGS = #-lreadline -L/Users/jae-kim/.brew/opt/readline/lib -I/Users/jae-kim/.brew/opt/readline/include

RM = rm
RMFLAGS = -rf

INC_DIR = .
SRC_DIR = .
OBJ_DIR = .

# libft
LIBFT = libft.a
LIBFT_DIR = lib/libft
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)
LIBFT_FLAGS = -L./$(LIBFT_DIR) -lft

HEADERS = $(addprefix $(INC_DIR)/, \
	minishell.h	\
)


ROOT_SRCS = $(addprefix $(SRC_DIR)/,	\
	minishell.c \
	init.c \
	execute.c \
	interpreter.c  \
	lexer_get_item.c \
	lexer.c  \
	parse_cmd.c \
	parse_get_node.c \
	parse_type_check.c  \
	parser.c  \
	print_JSON.c \
	symantic_analyzer.c \
	util.c \
)

SRCS = \
	$(ROOT_SRCS)	\

vpath %.c \
	$(SRC_DIR)	\



OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all : $(NAME)

clean :
	@$(RM) $(RMFLAGS) $(OBJ_DIR)


fclean : clean
	@$(RM) $(RMFLAGS) $(NAME)


re : fclean all

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c $(LIBFT_FILE) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(RLFLAGS) -c $< -o $@


$(NAME) : $(LIBFT_FILE)  $(OBJS)
	@$(CC) $(CFLAGS) $(RLFLAGS) $(LIBFT_FLAGS) $(OBJS) -o $@


# lib
lib : libft
lib_fclean : libft_fclean
lib_re : lib_fclean lib

# libft
libft : $(LIBFT_FILE)

$(LIBFT_FILE) :
	@make --no-print-directory -C $(LIBFT_DIR)

libft_re :
	@make --no-print-directory -C $(LIBFT_DIR) re

libft_clean :
	@make --no-print-directory -C $(LIBFT_DIR) clean

libft_fclean :
	@make --no-print-directory -C $(LIBFT_DIR) fclean


.PHONY: all clean fclean re bonus \
	lib lib_re	\
	libft libft_clean libft_fclean


