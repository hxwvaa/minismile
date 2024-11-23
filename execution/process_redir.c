#include "../minishell.h"



int handle_here_doc(t_redir *temp, int *input)
{
    int hdpipe[2];

    if(*input != STDIN_FILENO && *input != -1)
        close(*input);
    pipe(hdpipe); // protect 
    write(hdpipe[1], temp->hd_input, ft_strlen(temp->hd_input));
    close(hdpipe[1]);
    free(temp->hd_input);
    temp->hd_input = NULL;
    *input = hdpipe[0];
    return (0);
}

int handle_redir_in(t_redir *temp, int *input, int *output, t_cmd *curr)
{
    int pipefd[2]; // idk if it will compile it might say unused variable

	if(*input != STDIN_FILENO && *input != -1)
        close(*input);
    *input = open(temp->file, O_RDONLY);
    if(*input == -1)
    {
        perror(temp->file);
        pipe(pipefd); // need to protect
        close(pipefd[1]);
        *input = pipefd[0];
        if(*output != STDOUT_FILENO && *output != -1)
        {
            close(*output);
            *output = -1; //without this caused ls output be printed in results.txt "ls >results.txt <er | ls | cat | wc -l"
        }
        curr->redir_out = 0;
        return (-1);
    }
    return (0);
}

int handle_redir_out(t_redir *temp, int *output, int *input, t_cmd *curr)
{
    if(*output != STDOUT_FILENO && *output != -1)
        close(*output);
    if(temp->flag == 1)
        *output = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (temp->flag == 3)
        *output = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    curr->redir_out = 1;
    if(*output == -1)
    {
        perror(temp->file);
        if(*input != STDIN_FILENO && *input != -1)
            close(*input);
        curr->redir_out = 0;
        return(-1);
    }
    return (0);
}

int process_redir(t_cmd *curr, int *input, int *output)
{
    t_redir *temp;

    temp = curr->redirs;
    while(temp)
    {
        if(temp->flag == 2)
        {
            if(handle_heredoc(temp, input) == -1)
            return (-1);
        }
        else if(temp->flag == 0)
        {
            if(handle_redir_in(temp, input, output, curr) == -1)
                return(-1);
        }
        else if(temp->flag == 1 || temp->flag == 3)
        {
            if (handle_redir_out(temp, output, input, curr) == -1)
                return (-1);
        }
        temp = temp->next;
    }
    return (0);
}