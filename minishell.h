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
    int type;
}t_token;

typedef struct s_toklist{
    char *token;
    int type;
    struct s_toklist *next;
}t_toklist;

typedef struct s_cmd{
    
    char *cmd;
    char **cargs;
    char *inf;
    char *outf;
    char *limiter;
    int app;
    struct s_cmd *next;
}t_cmd;

typedef struct s_shell{
    
    char **envi;
    t_list *envir;
    t_toklist *tokens;
    t_cmd *cmds;
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

//---------------------pre_execute------------------//
t_token *array_to_token_array(char **split, int count);

t_toklist *array_token_list(t_shell *data, char **split, int count);
//void array_token_list(t_shell *data, char **split, int count);

t_cmd *our_toklist_cmdlist(t_toklist *list, t_shell *data);
int count_args(t_toklist *list);
//---------------------free_arr_list------------------//
void	free_arr(char **arr);
void	our_envlistclear(t_list **envir);
void	our_toklistclear(t_toklist **tokens);

void	exit_shell(char **av, t_shell *data);






#endif

//// askjdsakjdh asldkhas d> ask<sajdg " " | dksa | sadlasd > asdk ;