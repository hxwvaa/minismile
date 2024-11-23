#include "../minishell.h"

//need to norm still
char *do_heredoc(char *delimiter)
{
    char *limit;
    char *line;
    char *input;
    char *temp;

    input = ft_strdup("");
    limit = ft_strjoin(delimiter, "\n");
    if(!limit)
        return (NULL);
    while(1)
    {
        line = get_next_line(0);
        if(line)//idk if this how we do it, it doesnt segfault now
        {
            if(ft_strncmp(limit, line, ft_strlen(limit)) == 0)
            {
                free(limit);
                free(line);
                break ;
            }
            temp = ft_strjoin(input, line);
            free(input);
            if(!temp)
                return (free(line), free(limit), NULL);
            input = temp;
            free(line);
        }
        else
        {
            free(limit);
            break ;
        } // idk if this how it should be
    }
    return (input);
}
void process_heredoc(t_cmd *cmds)
{
    t_cmd *curr;
    t_redir *temp;

    curr = cmds;
    while(curr)
    {
        temp = curr->redirs; // maybe check if curr->inputs is null before assigning
        while(temp)
        {
            if(temp->flag == 2)
            {
                temp->hd_input = do_heredoc(temp->file);
                if(!temp->hd_input)
                {
                    perror("malloc");
                    return ;
                }
            }
            else
                temp->hd_input = NULL;
            temp = temp->next;
        }
        curr = curr->next;
    }
}

void reset_stds(t_shell *data)
{
    dup2(data->std[0], STDIN_FILENO);
    dup2(data->std[1], STDOUT_FILENO);
    close(data->std[0]);
    close(data->std[1]);
}

// dont forget before calling this function process here_doc, dup stds in&out
void our_execution(t_shell *data, int input, int output)
{
    t_cmd *curr;
    int status;

    curr = data->cmds;
    while(curr)
    {
        if(process_redir(curr, &input, &output) == -1)
        {
            curr = curr->next;
            continue ;
        }
        if(curr->next && pipe(data->fd) == -1)
            perror("pipe");
        if(is_builtin(curr->cmd) && only_one_cmd(data->cmds) == 1)
        {
            set_redirection(curr, data, &input, &output);
            execute_one_cmd(curr, data);
        }
        else
            fork_execute_child(data, curr, &input, &output);
        curr = curr->next;
    }
    close_clean(data, input, output);
    while(wait(&status) > 0);
    reset_stds(data);
}

void pre_execute(t_shell *data, int input, int output)
{
    data->std[0] = dup(STDIN_FILENO);
    data->std[1] = dup(STDOUT_FILENO);
    process_heredoc(data->cmds);
    our_execution(data, input, output);
}
