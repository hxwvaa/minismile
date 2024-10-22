#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdint.h>
# include <sys/wait.h>
#include <stdbool.h>

typedef enum S_TYPES{

    CMD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND
}t_type;

typedef struct s_token{

    char *token;
    t_type type;
}t_token;

typedef struct s_cmd{
    
    char *cmd;
    char **cargs;
    char *inf;
    char *out;
    int   app;
    struct s_cmd *next;
}t_cmd;

typedef struct s_shell{
    
    char **envi;
    char **our_args;
}t_shell;

char	*ft_strtrim(char const *s1, char const *set);
char **our_tokenize(char *s);
char	*get_cmd_path(char *cmd, char **env);
int	our_quote(char *str, int i, char quote);


#endif