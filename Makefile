NAME = minishell

SRC = minislime.c tokenize.c libft/ft_strtrim.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra 

DEL = rm -rf

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC)  $^ -o $@ -lreadline

clean:
	$(DEL) $(OBJ)
fclean: clean
	$(DEL) $(NAME)

re: fclean all

.PHONY: all clean fclean re