#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*ft_strtrim(char const *s1, char const *set);
char **our_tokenize(char *s);
char	*get_cmd_path(char *cmd, char **env);
int	our_quote(char *str, int i, char quote);


#endif