NAME = minishell

EXEC = execution

SRC = minislime.c tokenize.c findpath.c builtin/our_echo.c\
		builtin/our_env.c builtin/our_pwd.c builtin/our_unset.c\
		builtin/our_export.c builtin/our_cd.c builtin/our_exit.c\
		pre_execute.c free_arr_list.c toklist_cmdlist.c\
		gnl/get_next_line.c $(EXEC)/execution.c $(EXEC)/process_hd.c\
		$(EXEC)/process_redir.c $(EXEC)/builtin_execute.c\
		$(EXEC)/execute_child.c $(EXEC)/execute_parent.c\
		$(EXEC)/exec_utils.c $(EXEC)/findpath.c


OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

DEL = rm -rf

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(CY)Building libft$(RC)"
	@make bonus -C $(LIBFT_DIR)

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(CY)Generating minishell$(RC)"
	@$(CC) -o $@ $^ -lreadline $(LIBFT)

clean:
	@echo "$(YE)Cleaning all object files$(RC)\n"
	@make clean -C $(LIBFT_DIR)
	@$(DEL) $(OBJ)

fclean: clean
	@echo "$(YE)Cleaning all additional objects and libraries$(RC)\n"
	@make fclean -C $(LIBFT_DIR)
	@$(DEL) $(NAME)

re: fclean all

valgrind: $(NAME)
	sh ak.sh

.PHONY: all clean fclean re
