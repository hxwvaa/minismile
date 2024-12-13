/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:20:06 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/12 20:55:09 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void reset_stds(t_shell *data)
{
    dup2(data->std[0], STDIN_FILENO);
    dup2(data->std[1], STDOUT_FILENO);
    if(data->std[0] != -1)
    {
        close(data->std[0]);
        data->std[0] = -1;
    }
    //close(data->std[0]);
    if(data->std[1] != -1)
    {
        close(data->std[1]);
        data->std[1] = -1;
    }
    //close(data->std[1]);
}

void our_execution(t_shell *data, int input, int output)
{
    t_cmd *curr;

    curr = data->cmds;
    while(curr)
    {
        if(process_redir(curr, &input, &output) == -1)
        {
            data->exit_code = 1;
            curr = curr->next;
            continue ;
        }
        if(curr->em_expand)
        {
            data->exit_code = 0;
            curr = curr->next;
            continue;
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
    close_clean(data, input, output); // if i move it out i get fd leaks
}



void wait_loop(t_shell * data, int status, pid_t pid)
{
    while((pid = wait(&status)) > 0)
    {
        if(pid == data->lpid)
        {
            if(WIFSIGNALED(status))
            {
                if (WTERMSIG(status) == SIGINT)
                {
                    data->exit_code = 130;
                    g_signo = 0;
                }
                else if(WTERMSIG(status) == SIGSEGV)
                {
                    write(2, "Segmentation fault: 11\n", 23);
                    data->exit_code = 139; // i think this will catch the segfault
                }
                else if (WTERMSIG(status) == SIGQUIT)
                {
                    write(2, "Quit: 3\n", 8);
                    data->exit_code = 131;
                }
            }
            else
                data->exit_code = WEXITSTATUS(status);
        }
    }
}

void pre_execute(t_shell *data, int input, int output)
{
    int status;
    int check;
    pid_t pid;
    
    status = 0;
    pid = 0;
    check = process_heredoc(data->cmds, data);
    if (check == 12 || check == -1)
    {
        if(check == 12)
        {
            free_all(data);
            exit(errno);
        }
        data->exit_code = 130;
        g_signo = 0;
        return ;
    }
    data->std[0] = dup(STDIN_FILENO);
    data->std[1] = dup(STDOUT_FILENO);
    data->envi = envlist_envarray(data->envir);
    if(!data->envi)
        perror("malloc");
    our_execution(data, input, output);
    wait_loop(data, status, pid);
    reset_stds(data);
}
