#!/bin/bash
rm ./minishell
gcc -Wall -Wextra -Werror -o minishell *.c  -L ./lib/libft -lft -lreadline -L/Users/jae-kim/.brew/opt/readline/lib -I/Users/jae-kim/.brew/opt/readline/include
./minishell
