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

#define CD_ERR_1 "cd: error retrieving current directory:"
#define CD_ERR_2 " getcwd: cannot access parent directories:"
#define CD_ERR_3 " No such file or directory\n"

extern int g_signo;

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
    char *line;
    char *backup_pwd;
    t_list *envir;
    t_toklist *tokens;
    t_cmd *cmds;
    char *cmd_path;
    char **our_args;
    int fd[2];
    int std[2];
    int   pid;
    int     exit_code;
    int lpid;
    
}t_shell;

// replace_line for signal
void rl_replace_line (const char *text, int clear_undo);

void	read_loop(t_shell *data);
char	*ft_strtrim(char const *s1, char const *set);
char **our_tokenize(char *s);
char	*get_cmd_path(char *cmd, int *input, int *output, t_shell *data);
int	our_quote(char *str, int i, char quote);

//---------------------builtins------------------//
void our_echo(char **arg, t_shell *data);
void our_expenv(t_shell *data);
int our_env(t_list *envir, char **arg, t_shell *data);
bool our_pwd(t_shell *data);
char *our_pwd_help(t_shell *data);
char *get_value_env(char *var, t_shell *data);
char *get_curr_pwd(void);
char *get_pwd_value(t_shell *data);
int del_dir(char *path, char *prevdir, t_shell *data);
int update_pwd(t_shell *data, char *pwd);
int update_oldpwd(t_shell *data, char *oldpwd);
bool our_unset(char **var, t_list **envir);
bool our_export(char **arg, t_shell *data, int i);
int our_cdir(char *path, t_shell *data);


void	protected_write(char *error, int fd, t_shell *data);
int	is_digit_exit_code(char **av);
bool	is_num_very_small(char *str);

char *our_expand(char *var, t_shell *data);
char *before_equal(char *str);

//---------------------pre_execute------------------//

t_toklist *array_token_list(t_shell *data, char **split, int count);
//void array_token_list(t_shell *data, char **split, int count);

t_cmd *our_toklist_cmdlist(t_toklist *list, t_shell *data);
char **envlist_envarray(t_list *env);
//----------------------parsing---------------------//
int	check_syntax(char **av, int i, t_shell *data);
int our_extok(t_toklist *tokens, t_shell *data);
int find_dollar(char *str);
char *pre_dollar(char *str, char *bef_do);
char *join_free(char *s1, char *s2);
char *handle_ex(char *str, char *res, int *i, t_shell *data);
char *handle_dq(t_toklist *temp, char *res, int *i, t_shell *data);
char *handle_sq(char *str, char *res, int *i);
char *handle_any(char *str, char *res, int *i);
int check_quotes(t_toklist *list, t_shell *data);
int	our_free(char **str, int t);
int	our_fill(char *s, char **cmd, int count);
int	our_quote(char *str, int i, char quote);
t_cmd *our_clstlast(t_cmd *lst);
int our_clstadd_back(t_cmd **lst, t_cmd *new);
t_redir *our_redirlast(t_redir *lst);
t_redir *our_redirnew(char *file, int flag);
int our_rediradd(t_redir **lst, char *file, int flag);
t_cmd *our_clistnew(int count);
t_cmd *new_node(t_toklist *temp, t_shell *data, int *new_cmd);
void exit_free(t_shell *data);
int store_cmd(t_cmd *curr, t_toklist *temp);
int process_args(t_cmd *curr, t_toklist *temp, int i);
int count_args(t_toklist *list);
//-----------hd_expansions && hd_ex_utiils---------//
char    *expand_hd(char *line, t_shell *data, int len);
char *join_strs(char *s1, char *s2, char *line);
char *expand_what(char *line, int start, int *len);
char *final_string(char *line, char *res);
char *update_line(char *line, char *res, int len);
char    *handle_expand(char *line, t_shell *data, int *len, char *res);
//---------------------execution------------------//
void pre_execute(t_shell *data, int input, int output);
void wait_loop(t_shell *data, int status, pid_t pid);
void hd_clean_exit(int exit_code, int flag, int pipefd[], t_shell *data);
void handle_hd_sig(int signo);
void signal_hd(int signo);
char	*do_heredoc(int fd, char *limit, t_shell *data);
int count_bytes(int fd, char *temp, int *total);
int process_heredoc(t_cmd *cmds, t_shell *data);
int process_redir(t_cmd *curr, int *input, int *output, t_shell *data);
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
void wait_loop(t_shell * data, int status, pid_t pid);

//---------------------free_arr_list------------------//
void	free_arr(char **arr);
void	our_envlistclear(t_list **envir);
void	our_toklistclear(t_toklist **tokens);
void    our_cmdlistclear(t_cmd **list);

void	exit_shell(char **av, t_shell *data, int *exit_status);
size_t len_b4_eq(char *arg);

void free_exec_fail(t_shell *data, int *input, int *output, int exit_code);
void free_all(t_shell *data);
void handle_signal(int sig);
int	check_exp_ident(char *arg);


#endif