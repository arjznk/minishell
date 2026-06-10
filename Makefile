
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRCS = main.c tokenisation/get_env.c tokenisation/tokenisation.c utils/list_functions.c parsing/parsing.c builtins/cd.c builtins/echo.c \
builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c exec/exec.c free/free_all.c utils/str_utils.c utils/utils.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I./libft
 
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME) 

$(LIBFT):
	make -C $(LIBFT_DIR)
	
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re