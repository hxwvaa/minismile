#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*ft_strtrim(char const *s1, char const *set);
char **ft_tokenize(char *s);

#endif