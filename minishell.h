#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
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
char **ft_tokenize(char *s);
char	*ft_strchr(const char *s, int c);
//int	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
void    execute_cmd(char **cmd, char **env);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	**st_tokenize(char *s);
void    pre_execute_cmd(char **cmd, char **env);
char	*get_cmd_path(char *cmd, char **env);


#endif