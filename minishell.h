#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include "gnl/get_next_line.h"
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
#include <sys/stat.h>
#include <signal.h>

// define a macro for cd error message

typedef enum S_TYPES{

    CMD,
    FLAG,
    ARGS,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    HERE_DOC,
    FILE_NAME,
    LIMITER,
    EXPAND,
    APPEND,
    SQ,
    DQ

}t_type;

typedef struct s_token{

    char *token;
    int type;
    int q_type;
}t_token;

typedef struct s_toklist{
    char *token;
    int type;
    int q_type;
    int em_ex;
    struct s_toklist *next;
}t_toklist;

typedef struct s_redir{
    char *file;
    char *hd_input;
    int flag;
    struct s_redir *next;
}t_redir;

typedef struct s_cmd{
    
    char *cmd;
    char **cargs;
    t_redir *redirs;
    int redir_out;
    int em_expand;
    struct s_cmd *next;
}t_cmd;

typedef struct s_shell{
    
    char **envi;
    t_list *envir;
    t_toklist *tokens;
    t_cmd *cmds;
    char *cmd_path;
    char **our_args;
    int fd[2];
    int std[2];
    int   pid;
    int     exit_code;
    int lpid; // didnt initialize in init shell yet but it is working fine without initializing
    
}t_shell;

char	*ft_strtrim(char const *s1, char const *set);
char **our_tokenize(char *s);
char	*get_cmd_path(char *cmd, char **env);
int	our_quote(char *str, int i, char quote);
void rm_quotes(t_toklist *tokens);//not needed
int expand_tokens(t_toklist *tokens, t_shell *data);//not needed

//---------------------builtins------------------//
void our_echo(char **arg, t_shell *data);
void our_expenv(t_shell *data);
void our_env(t_list *envir);
bool our_pwd(void);
//int our_pwd();
char *get_pwd(void);
bool our_unset(char *var, t_list **envir);
bool our_export(char **arg, t_shell *data, int i);
int our_cdir(char *path, t_shell *data);


char *our_expand(char *var, t_shell *data);

//---------------------pre_execute------------------//
t_token *array_to_token_array(char **split, int count);

t_toklist *array_token_list(t_shell *data, char **split, int count);
//void array_token_list(t_shell *data, char **split, int count);

t_cmd *our_toklist_cmdlist(t_toklist *list, t_shell *data);
char **envlist_envarray(t_list *env);
//----------------------parsing---------------------//
int our_extok(t_toklist *tokens, t_shell *data);
int find_dollar(char *str);
char *pre_dollar(char *str, char *bef_do);
char *join_free(char *s1, char *s2);
char *handle_ex(char *str, char *res, int *i, t_shell *data);
char *handle_dq(char *str, char *res, int *i, t_shell *data);
char *handle_sq(char *str, char *res, int *i);
char *handle_any(char *str, char *res, int *i);
int check_quotes(t_toklist *list);
//-----------hd_expansions && hd_ex_utiils---------//
char    *expand_hd(char *line, t_shell *data, int len);
int append_input(char **input, char *line);
char *join_strs(char *s1, char *s2, char *line);
char *expand_what(char *line, int start, int *len);
char *final_string(char *line, char *res);
char *update_line(char *line, char *res, int len);
char    *handle_expand(char *line, t_shell *data, int *len, char *res);
//---------------------execution------------------//
// int is_builtin(char *cmd);
// int execute_one_cmd(t_cmd *curr, t_shell *data);
// int only_one_cmd(t_cmd *cmd);
//void our_execution(t_shell *data);
//void execution(t_shell *data, int input, int output);
void pre_execute(t_shell *data, int input, int output);
void process_heredoc(t_cmd *cmds, t_shell *data);
int process_redir(t_cmd *curr, int *input, int *output);
int is_builtin(char *cmd);
int only_one_cmd(t_cmd *cmd);
int execute_one_cmd(t_cmd *curr, t_shell *data);
void set_redirection(t_cmd *curr, t_shell *data, int *input, int *output);
void fork_execute_child(t_shell *data, t_cmd *curr, int *input, int *output);
void builtin_pipeline(t_cmd *curr, t_shell *data);
void prepare_fds(int *input, int *output, t_shell *data, t_cmd *curr);
void close_clean(t_shell *data, int input, int output);
void invalid_lstcmd(char *file, int *input, int *output, t_shell *data);
void invalid_cmd_dir(char *file, int *input, int *output, t_shell *data);
int check_if_directory(char *cmd);

//---------------------free_arr_list------------------//
void	free_arr(char **arr);
void	our_envlistclear(t_list **envir);
void	our_toklistclear(t_toklist **tokens);
void    our_cmdlistclear(t_cmd **list);

void	exit_shell(char **av, t_shell *data);






#endif