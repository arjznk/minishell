
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRCS = main.c parsing/get_env.c parsing/tokenisation.c utils/list_functions.c utils/utils.c \
builtins/pwd.c builtins/cd.c builtins/exit.c

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