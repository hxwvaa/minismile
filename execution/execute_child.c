/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:19:55 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/01 20:58:38 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void close_clean(t_shell *data, int input, int output)
{
    //write(2, "inside close clean\n", 19);
    if(input != STDIN_FILENO && input != -1)
        close(input);
    if (output != STDOUT_FILENO && output != -1)
        close(output);
    if(data->fd[0] != -1)
    {
        close(data->fd[0]);
        data->fd[0] = -1;
    }
    if(data->fd[1] != -1)
    {
        close(data->fd[1]);
        data->fd[1] = -1;
    }
    if(data->envi)
      free_arr(data->envi);
}

void set_redirection(t_cmd *curr, t_shell *data, int *input, int *output)
{
    if(*input != STDIN_FILENO && *input != -1)
    {
        dup2(*input, STDIN_FILENO);
        close(*input);
        *input = -1;
    }
    if(*output != STDOUT_FILENO && *output != -1)// or move this above and make if(curr->next && data->fd[1] != -1) an else if
    {
        dup2(*output, STDOUT_FILENO);
        close(*output);
        *output = -1;
        if(data->fd[1] != -1)
            close(data->fd[1]);
        // if(data->fd[0] != -1)
        //     close(data->fd[0]);
    }
    else if(curr->next && data->fd[1] != -1)
    {
        if(dup2(data->fd[1], STDOUT_FILENO) == -1)
            write(2, "error dup2\n", 11);
        if(data->fd[1] != -1)    
            close(data->fd[1]);
        if (data->fd[0] != -1)
            close(data->fd[0]); // casuses the sigpipe // pwd | ls doesnt sigpipe in our_minishell
        data->fd[0] = -1; //idk if needed
        data->fd[1] = -1;
    }
}

void cleanup_child(t_shell *data, int *input, int *output)
{
    if(data->std[0] != -1)
        close(data->std[0]);
    if(data->std[1] != -1)
        close(data->std[1]);
    if(*input != -1)
	    close(*input);
    if(*output != -1)
	    close(*output);
    if(data->fd[0] != -1)    
        close(data->fd[0]); // if there is no cmd i need to close it or i get fd leak
    if(data->tokens)
        our_toklistclear(&data->tokens);
    if(data->envir)
        our_envlistclear(&data->envir);
    if(data->cmds) 
        our_cmdlistclear(&data->cmds);
    if(data->envi)
        free_arr(data->envi);
}

void execute_child(t_shell *data, t_cmd *curr, int *input, int *output)
{
    //signal(SIGPIPE, handle_sigpipe);
    set_redirection(curr, data, input, output);
    if(curr->cmd)
    {
        if(data->std[0] != -1)
            close(data->std[0]);
        if(data->std[1] != -1)
            close(data->std[1]);
        // if (is_builtin(curr->cmd))
        //     builtin_pipeline(curr, data);
        if(data->fd[0] != -1)    
            close(data->fd[0]);// not needed ? //sigpipe signal 13 is non-builtin | < Makefile wc -l // if i dont add it fd leaks
        //if(check_if_directory(curr->cmd)) // maybe i need to check if there is / first, because if i write builtin it shows the dir error idk if its correct or no
        // fprintf(stderr, "\033[32;1m%s\033[0m\n", curr->cmd);
        
        if(ft_strchr(curr->cmd, '/') && check_if_directory(curr->cmd))
            invalid_cmd_dir(curr->cmd, input, output, data);
        data->cmd_path = get_cmd_path(curr->cmd, data->envi);
        if (!data->cmd_path)
            invalid_lstcmd(curr->cmd, input, output, data);
        if (execve(data->cmd_path, curr->cargs, data->envi) == -1) // if it fails even  though it is a valid command maybe because i malloc more space??
            invalid_lstcmd(curr->cmd, input, output, data); // dont forget to free data->envi, and change exit_code var 127
    }
    cleanup_child(data, input, output); // maybe change name misleading
    data->exit_code = 0; // maybe global variable instead cause this in child it wont matter
	exit(0);
}

void fork_execute_child(t_shell *data, t_cmd *curr, int *input, int *output)
{
    data->pid = fork();
    if(data->pid == -1)
        perror("fork");
    if(data->pid == 0)
        execute_child(data, curr, input, output);
    prepare_fds(input, output, data, curr);
    if(!curr->next)
        data->lpid = data->pid; // do i need to initialize in init_shell ?
}
