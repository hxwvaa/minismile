/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:19:47 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/05 16:26:07 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// change this function
int only_one_cmd(t_cmd *cmd) 
{
    t_cmd *curr;
    int i;

    i = 0;
    curr = cmd;
    // while(curr && curr->cmd)
    // {
    //     i++;
    //     curr = curr->next;
    // }
    while(curr)
    {
        i++;
        curr= curr->next;
    }  
    if(i == 1)
        return(1);
    return (0);
}

void clean_exit(t_shell *data, int r)
{
     if(data->envir)
        our_envlistclear(&data->envir);
    if(data->tokens)
        our_toklistclear(&data->tokens);
    if(data->cmds) 
        our_cmdlistclear(&data->cmds);
    if(data->envi)
        free_arr(data->envi);
    //close(data->fd[0]); // to close read end after writing to the pipe
    if(r == 0)
        exit(0);
    else    
        exit(1);
}

int is_builtin(char *cmd)
{
    if(!cmd)
        return(0);
    if (ft_strncmp(cmd, "exit", 5) == 0)
        return (1);
    else if(ft_strncmp(cmd, "env", 4) == 0)
        return (1);
    else if(ft_strncmp(cmd, "unset", 6) == 0)
        return (1);
    else if(ft_strncmp(cmd, "echo", 5) == 0)
        return (1);
    else if(ft_strncmp(cmd, "export", 7)== 0)
        return (1);
    else if(ft_strncmp(cmd, "pwd", 4) == 0)
        return(1);
    else if(ft_strncmp(cmd, "cd", 3) == 0)
        return (1);
    else    
        return (0);
}

int execute_one_cmd(t_cmd *curr, t_shell *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (ft_strncmp(curr->cmd, "exit", 5) == 0)
        exit_shell(curr->cargs, data);
    else if(ft_strncmp(curr->cmd, "env", 4) == 0)
        our_env(data->envir);
    else if(ft_strncmp(curr->cmd, "unset", 6) == 0)
        our_unset(curr->cargs[i + 1], &data->envir);
    else if(ft_strncmp(curr->cmd, "echo", 5) == 0)
        our_echo(curr->cargs, data);
    else if(ft_strncmp(curr->cmd, "export", 7)== 0)
        j = our_export(curr->cargs, data, 0);
    else if(ft_strncmp(curr->cmd, "pwd", 4) == 0)
        j = our_pwd();
    else if(ft_strncmp(curr->cmd, "cd", 3) == 0)
        our_cdir(curr->cargs[i + 1], data);
    if (j == -1)
        ; //exit cleanly
    return(j);
}

void builtin_pipeline(t_cmd *curr, t_shell *data)
{
    int r;
    
    close(data->fd[0]);
    r = execute_one_cmd(curr, data);
    if(r == 0) 
        clean_exit(data, r);
    else
        clean_exit(data, r);
}
//close(data->fd[0]);//this causes sigpipe

