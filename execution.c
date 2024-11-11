/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:53:00 by mshaheen          #+#    #+#             */
/*   Updated: 2024/11/11 21:34:56 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add a function that check for limiter for all
//i can just check  if limiter is not null
int do_heredoc(char *limiter, t_shell *data)
{
    char *limit;
    char *line;
    
    if(pipe(data->fd[2]) == -1)
        perror("pipe");     
    limit = ft_strjoin(limiter, "\n");
    if(!limit)
        return (0);
    while(1)
    {
        line = get_next_line(0);
        if(ft_strncmp(limiter, line, ft_strlen(limiter) + 1)== 0)
        {
            free(limit);
            free(line);
            close(data->fd[1]);
            return ; // break ??
        }
        ft_putstr(line, data->fd[1]);
        free(line);
    }
    if(limit)
        free(limit);
    //close(data->fd[1]); 
    return (data->fd[0]);
}

// void only_one_cmd(t_cmd *cmd)
// {
//     //need to check if builtin
//     check_infile_outfile()
// }

char **envlist_envarray(t_list *env)
{
    char **env_arr;
    t_list *curr;
    int i;
    i = ft_lstsize(env);
    env_arr = ft_calloc((i + 1), sizeof(char *));
    if(!env_arr)
        return(perror("malloc"), NULL);
    i = 0;
    curr = env;
    while(curr)
    {
        env_arr[i] = ft_strdup(curr->content);
        if(!env_arr[i])
        {
            while(i > 0)
                free(env_arr[i--]);
            free(env_arr);
            return(NULL);
        }
        i++;
        curr = curr->next;
    }
    return(env_arr);   
}

void	input_invalid(char *file)
{
	write(2, "minishell: no such file or directory: ", 38);
	ft_putendl(file, 2);
}

void output_invalid(char *file, int ifd)
{
    write(2, "minishell: operation not permitted: ", 36);
	ft_putendl(file, 2);
	close(ifd);
	exit(1);
}
void invalid_cmd(char *file, t_shell *data)
{}
void invalid_lstcmd(char *file, t_shell *data);

int is_builtin(char *cmd)
{
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

//void execute_builtin()

void our_execution(t_shell *data)
{
    t_cmd *curr;
    int status;
    int input;
    int output;
    char **env;

    data->envi = envlist_envarray(data->envir);
    if(!data->envi) // add error message env is NULL
        return ;
    input = STDIN_FILENO;
    curr = data->cmds;
    // if(curr->next == NULL)
    //     only_one_cmd(data->cmds);
    // i need to check how many here_doc there are and do the here_doc before executing the cmds
    while(curr)
    {
        if(!curr->inf && curr->limiter)
        {
            do_heredoc(curr->limiter, data);
        }
        else if(curr->inf)
        {
            input = open(curr->inf, O_RDONLY, 0777);
            if(input == -1)
                input_invalid(curr->inf);  
        }
        if(curr->next && pipe(data->fd) == -1)
            perror("pipe");
        if(is_builtin(curr->cmd))
            //function to execute_builtin()
        else // this could all be a separate function
        {
            data->pid = fork();
            if(data->pid == -1)
                perror("fork");
            if(data->pid == 0)
            {
                if(input != STDIN_FILENO)
                {
                    dup2(input, STDIN_FILENO);
                    close(input);
                }
                if(curr->next)
                {
                    dup2(data->fd[1], STDOUT_FILENO);
                    close(data->fd[1]);
                    close(data->fd[0]);
                }
                else if(curr->outf)
                {
                    if(curr->app)
                        output = open(curr->outf,O_WRONLY | O_CREAT | O_APPEND, 0644);
                    else
                        output = open(curr->outf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if(output == -1)
                        output_invalid(curr->outf, data->fd[0]); // dont know about the fd
                    if (output != STDOUT_FILENO)
                    {
                        dup2(output, STDOUT_FILENO);
                        close(output);
                    }
                }
                //find path for cmd cmd_path
                data->cmd_path = get_cmd_path(curr->cmd, data->envi);
                if (execve(curr->cmd, curr->cargs, data->envi) == -1)
                {
                    if(curr->next)
                        invalid_cmd(curr->cmd, data); //we pass data to close fds, maybe i should
                    else
                        invalid_lstcmd(curr->cmd, data); // dont forget to free data->envi, and change exit_code var 127
                }
            }

            if(input != STDIN_FILENO)
                close(input);
            if(curr->next)
                close(data->fd[1]);
            curr = curr->next;
        }
    }
    //if(data->envi)
    //  free_arr(data->envi)
    while(wait(&status) > 0);
}
