#!/bin/bash
rm ./minishell
gcc -Wall -Wextra -Werror -o minishell *.c  -fsanitize=address -L ./lib/libft -lft -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
./minishell 

#readline directory /Users/nick-name 
