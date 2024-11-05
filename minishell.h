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
# include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>

// define a macro for cd error message

typedef enum S_TYPES{

    CMD,
    FLAG,
    ARGS,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    HERE_DOC,
    LIMITER,
    EXPAND,
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
    char *outf;
    struct s_cmd *next;
}t_cmd;

typedef struct s_shell{
    
    char **envi;
    t_list *envir;
    char **our_args;
    int     exit_code;
    
}t_shell;

char	*ft_strtrim(char const *s1, char const *set);
char **our_tokenize(char *s);
char	*get_cmd_path(char *cmd, char **env);
int	our_quote(char *str, int i, char quote);

//---------------------builtins------------------//
void our_echo(char **arg);
void our_expenv(t_shell *data);
void our_env(t_list *envir);
bool our_pwd(void);
char *get_pwd(void);
bool our_unset(char *var, t_list **envir);
bool our_export(char **arg, t_shell *data);
void our_cdir(char *path, t_shell *data);


void our_expand(char *var, t_shell *data);

void exit_shell(char **av);


#endif

//// askjdsakjdh asldkhas d> ask<sajdg " " | dksa | sadlasd > asdk ;