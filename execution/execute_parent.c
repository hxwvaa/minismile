/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:20:00 by mshaheen          #+#    #+#             */
/*   Updated: 2024/11/24 10:21:08 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void close_inp_fd(int *input)
{
    if(*input != STDIN_FILENO && *input != -1)
    {
        close(*input);
        *input = -1;
    }
}
void close_out_fd(int *output)
{
    if(*output != STDOUT_FILENO && *output != -1) 
    {
        close(*output);
        *output = -1;    
    }
}

void empty_pipe(int *input, t_shell *data)
{
    int em_fd[2];
    
    pipe(em_fd);
    if(data->fd[1] != -1)
        close(data->fd[1]);
    if(data->fd[0] != -1) 
        close(data->fd[0]);
    close(em_fd[1]);
    close(*input);
    *input = em_fd[0];
}

void redir_out_found(int *input, int *output, t_shell *data, t_cmd *curr)
{
    if(*input != STDIN_FILENO && *input != -1 && curr->next)
        empty_pipe(input, data);
    else
    {
        if(curr->next)
        {    
            if(data->fd[1] != -1)
                close(data->fd[1]);
            *input = data->fd[0];
        }
        else if (data->fd[0] != -1)
        {
            close(data->fd[0]);
            data->fd[0] = -1;
        }
    }
    data->fd[1] = -1;
    if(*output != STDOUT_FILENO && *output != -1) 
    {
        close(*output);
        *output = -1;
    }
    curr->redir_out = 0;
}

void prepare_fds(int *input, int *output, t_shell *data, t_cmd *curr)
{
    if(curr->redir_out == 1)
        redir_out_found(input, output, data, curr);
    else
    {
        close_inp_fd(input);
        if(curr->next)
        {    
            if(data->fd[1] != -1)
                close(data->fd[1]);
            *input = data->fd[0];
        }
        else if (data->fd[0] != -1)
        {
            close(data->fd[0]);
            data->fd[0] = -1;
        }
        data->fd[1] = -1;
        close_out_fd(output);
        curr->redir_out = 0;
    }  
}
