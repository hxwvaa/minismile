valgrind --trace-children=yes -s --suppressions=valgrind_script/ignore_readline_leaks.txt  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell