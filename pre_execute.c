#include "minishell.h"


//maybe add line to struct with t_type and set each string of line type

void token_type(char **line)
{
    t_token token;
    int i;

    i = 0;

    while(line && line[i])
    {
        if(line[i] == "|")
        {
            token.token = line[i];
            token.type = PIPE;
        }
        else if(line[i] == "<")
        {
            token.token = line[i];
            token.type = REDIR_IN;
        }
        else if(line[i] == ">")
        {
            token.token = line[i];
            token.type = REDIR_OUT;
        }
        else if(line[i] == ">" && line[i + 1] == ">")
        {
            token.token = line[i]; // strjoin them ??
            token.type = APPEND;
        }
        else if (*line[i] == '-')
        {
            token.token = line[i];
            token.type = FLAG;
        }
        else if () // need one for the cmd expand and limiter and here doc
    }
}

//t_cmd set_token_type(char **)