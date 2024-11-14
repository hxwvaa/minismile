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
// int do_heredoc(char *limiter, t_shell *data)
// {
//     char *limit;
//     char *line;
    
//     //if(pipe(data->fd) == -1)
//         //perror("pipe");     
//     limit = ft_strjoin(limiter, "\n");
//     if(!limit)
//         return (0);
//     while(1)
//     {
//         line = get_next_line(0);
//         if(ft_strncmp(limit, line, ft_strlen(limit)) == 0)
//         {
//             free(limit);
//             free(line);
//             close(data->fd[1]);
//             //return ;
//             break ;
//         }
//         ft_putstr_fd(line, data->fd[1]);
//         free(line);
//     }
//     // if(limit)
//     //     free(limit);
//    // close(data->fd[1]); 
//     return (data->fd[0]);
// }

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
        if(ft_strncmp(limit, line, ft_strlen(limit)) == 0)
        {
            free(limit);
            free(line);
            //close(data->fd[1]);
            //return ;
            break ;
        }
        temp = ft_strjoin(input, line);
        free(input);
        if(!temp)
            return (free(line), free(limit), NULL);
        //ft_putstr_fd(line, data->fd[1]);
        input = temp;
        free(line);
    }
    // if(limit)
    //     free(limit);
   // close(data->fd[1]); 
    return (input);
}

int only_one_cmd(t_cmd *cmd)
{
    t_cmd *curr;
    int i;

    i = 0;
    curr = cmd;
    while(curr && curr->cmd)
    {
        i++;
        curr = curr->next;
    }
    printf("cmd count:%d\n", i);    
    if(i == 1)
        return(1);
    return (0);
}

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
	ft_putendl_fd(file, 2);
}

void output_invalid(char *file, int ifd, t_shell *data)
{
    write(2, "minishell: operation not permitted: ", 36);
	ft_putendl_fd(file, 2);
	if(ifd != -1)
        close(ifd);
    if(data->envir)
        our_envlistclear(&data->envir);
    if(data->cmds) 
        our_cmdlistclear(&data->cmds);
    if(data->envi)
        free_arr(data->envi);
    data->exit_code = 127;
	exit(1);
}
void invalid_cmd(char *file, int input, t_shell *data)
{
    write(2, "minishell: command not found: ", 30);
	ft_putendl_fd(file, 2);
	//free_array(data->curr->cargs);
	close(input);
	close(data->fd[1]);
	close(data->fd[0]);
    exit_shell(data->cmds->cargs, data);
	exit(1);
}

void invalid_lstcmd(char *file, int input, int output, t_shell *data)
{
    write(2, "minishell: command not found: ", 30);
    ft_putstr_fd(file, 2);
    write(2, "\n", 1);
	//ft_putendl_fd(file, 2);
	//free_array(array);
    if(input != -1)
	    close(input);
    if(output != -1)
	    close(output);
    if(data->envir)
        our_envlistclear(&data->envir);
    if(data->cmds) 
        our_cmdlistclear(&data->cmds);
    if(data->envi)
        free_arr(data->envi);
    data->exit_code = 127;
    //exit_shell(data->cmds->cargs, data);
	exit(1);
}

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

void execute_one_cmd(t_cmd *curr, t_shell *data)
{
    int i;

    i = 0;
    if (ft_strncmp(curr->cmd, "exit", 5) == 0)
        exit_shell(curr->cargs, data);
    else if(ft_strncmp(curr->cmd, "env", 4) == 0)
        our_env(data->envir);
    else if(ft_strncmp(curr->cmd, "unset", 6) == 0)
        our_unset(curr->cargs[i + 1], &data->envir);
    else if(ft_strncmp(curr->cmd, "echo", 5) == 0)
        our_echo(curr->cargs);
    else if(ft_strncmp(curr->cmd, "export", 7)== 0)
        our_export(curr->cargs, data);
    else if(ft_strncmp(curr->cmd, "pwd", 4) == 0)
    {
        if(curr->cargs[i + 1] != NULL)
            write(2, "pwd: too many arguments\n", 24);
            //echo $?// data->exit_code = 1
        else    
            our_pwd();
    }
    else if(ft_strncmp(curr->cmd, "cd", 3) == 0)
        our_cdir(curr->cargs[i + 1], data);

}

void execute_builtin(t_cmd *curr, t_shell *data)
{
    int pid;
    
    // if(pipe(data->fd) == -1)
    //     perror("pipe");
    pid = fork();
    if(pid == -1)
        perror("fork");
    if(pid == 0)
    {
        close(data->fd[0]);
        dup2(data->fd[1], STDOUT_FILENO);
        close(data->fd[1]);
        execute_one_cmd(curr, data); // maybe i need to check if there is error in builtins
        exit(0);
    }
    else
        close(data->fd[1]);

}

void process_heredoc(t_cmd *cmds)
{
    t_cmd *curr;

    curr = cmds;
    while(curr)
    {
        if(curr->limiter)
        {
            curr->hd_input = do_heredoc(curr->limiter);
            //close(data->fd[1]);
            //printf("hd_fd: %d\n", curr->hd_fd);
            //close(data->fd[0]); hang program
            if(!curr->hd_input)
            {
                perror("malloc");
                return ;
            }
        }
        else
            curr->hd_input = NULL;
        curr = curr->next;
    }
    
}

void our_execution(t_shell *data)
{
    t_cmd *curr;
    int status;
    int input;
    int output = -1;
    //char *cpath;
    //char **env;

    data->envi = envlist_envarray(data->envir);
    if(!data->envi) // add error message env is NULL
        return ;
    input = STDIN_FILENO;
    // if(curr->next == NULL)
    //     only_one_cmd(data->cmds);
    // i need to check how many here_doc there are and do the here_doc before executing the cmds
    //function that process all here_docs first then come to the while loop store read end of pipe inside new var in cmd list hd_fd
    process_heredoc(data->cmds);
    curr = data->cmds;
    while(curr)
    {
        printf("start\n");
        //if(curr->hd_fd != -1)
        if(curr->hd_input)
        {
            if(input != STDIN_FILENO)
                close(input);
            int hdpipe[2];
            pipe(hdpipe);
            write(hdpipe[1], curr->hd_input, ft_strlen(curr->hd_input));
            close(hdpipe[1]);
           //input = curr->hd_fd;
           input = hdpipe[0];
           free(curr->hd_input);
           curr->hd_input = NULL;
           //curr->hd_fd = -1;
          // printf("input to hd_fd: %d\n", input);
           //close(data->fd[0]);
           //data->fd[0] = STDIN_FILENO;
        }
        else if(curr->inf)
        {
            input = open(curr->inf, O_RDONLY, 0777);
            //printf("inf opened:%d\n", input);
            if(input == -1)
            {
                input_invalid(curr->inf);
                curr = curr->next;  
                continue ;
            }
            // if(data->fd[0] != -1)
            // {close(data->fd[0]);
            // data->fd[0] = STDIN_FILENO;}
        }
        if(curr->next && pipe(data->fd) == -1)
            perror("pipe");
        if(is_builtin(curr->cmd) && only_one_cmd(data->cmds) == 1)
        {
            //if(only_one_cmd(data->cmds) == 1)
                execute_one_cmd(curr, data);
        }
        //     //else
        //     //{
        //         data->pid = fork();
        //         //int pid = fork();
        //         if(data->pid == 0)
        //         {
        //             if(input != STDIN_FILENO)
        //             {
        //                 dup2(input, STDIN_FILENO);
        //                 close(input);
        //             }
        //             if(curr->next)
        //             {
        //                 dup2(data->fd[1], STDOUT_FILENO);
        //                 if(data->fd[1] != -1)
        //                     close(data->fd[1]);
        //                 if(data->fd[0] != -1)
        //                     close(data->fd[0]);
        //             }
        //             else if(curr->outf)
        //             {
        //                 if(curr->app)
        //                     output = open(curr->outf,O_WRONLY | O_CREAT | O_APPEND, 0644);
        //                 else
        //                     output = open(curr->outf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        //                 if(output == -1)
        //                     output_invalid(curr->outf, data->fd[0]); // dont know about the fd
        //                 if (output != STDOUT_FILENO)
        //                 {
        //                     dup2(output, STDOUT_FILENO);
        //                     close(output);
        //                 }
        //             }
        //             execute_one_cmd(curr, data);
        //             if(data->envir)
        //                 our_envlistclear(&data->envir);
        //             if(data->cmds) 
        //                 our_cmdlistclear(&data->cmds);
        //             if(data->envi)
        //                 free_arr(data->envi);
        //             write(2, "did it reach\n", 13);
        //             printf("hello\n");
        //             //our_toklistclear(&data->tokens);
        //             exit(0);

        //        // }
        //     }    //execute_builtin(curr, data);
        //}//function to check if builtin without pipeline if yes execute that
            //else fork and execute builtin if there is pipeline
            //function to execute_builtin()

        else // this could all be a separate function
        {
            data->pid = fork();
            printf("after forl\n");
            if(data->pid == -1)
                perror("fork");
            if(data->pid == 0)
            {
                if(input != STDIN_FILENO)
                {
                    if(input != -1)
                    {   
                        dup2(input, STDIN_FILENO);
                    //printf("input dup closing:%d\n", input);
                        close(input);
                    }
                }
                if(curr->next)
                {
                    dup2(data->fd[1], STDOUT_FILENO);
                    if(data->fd[1] != -1)
                        close(data->fd[1]);
                    if(data->fd[0] != -1)
                        close(data->fd[0]);
                }
                if(curr->outf)
                {
                    if(curr->app)
                        output = open(curr->outf, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    else
                        output = open(curr->outf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if(output == -1)
                        output_invalid(curr->outf, data->fd[0], data); // dont know about the fd
                    if (output != STDOUT_FILENO)
                    {
                        dup2(output, STDOUT_FILENO);
                        close(output);
                    }
                }
                //find path for cmd cmd_path
                if (is_builtin(curr->cmd))
                {
                    execute_one_cmd(curr, data);
                    if(data->envir)
                        our_envlistclear(&data->envir);
                    if(data->cmds) 
                        our_cmdlistclear(&data->cmds);
                    if(data->envi)
                        free_arr(data->envi);
                    write(2, "did it reach\n", 13);
                    //printf("hello\n");
                    //our_toklistclear(&data->tokens);
                    exit(0);
                }  
                data->cmd_path = get_cmd_path(curr->cmd, data->envi);
                if(!data->cmd_path)
                {
                    //printf("i am in \n");
                    //if(curr->next)
                        //invalid_cmd(curr->cmd, input, data); 
                    // else
                         invalid_lstcmd(curr->cmd, input, output, data);
                } 
                //cpath = get_cmd_path(curr->cmd, data->envi);
                if (execve(data->cmd_path, curr->cargs, data->envi) == -1) // if it fails even  though it is a valid command maybe because i malloc more space??
                {
                    printf("execve failed\n");
                    if(curr->next)
                        invalid_cmd(curr->cmd, input, data); //we pass data to close fds, maybe i should
                    else
                        invalid_lstcmd(curr->cmd, input, output, data); // dont forget to free data->envi, and change exit_code var 127
                }
            }
            

        }

        if(input != STDIN_FILENO)
        {
            if(input != -1)
            //printf("input fd going to be closed:%d\n", input);   
                close(input);
        }
        // if(curr->hd_fd != -1)
        // {
        //     //printf("hd_closing:%d\n", curr->hd_fd);
        //     close(curr->hd_fd);
        // }
        if(curr->next)
            close(data->fd[1]);
        input = data->fd[0];
        data->fd[0] = -1;
        data->fd[1] = -1;
        if(output != STDOUT_FILENO)
        {
            if(output != -1)
                close(output);
            output = -1;
        }
        //printf("new input fd:%d\n", input);
        // if(!curr->next)
        //     close(data->fd[0]);
        curr = curr->next;
    }
    if(input != STDIN_FILENO)
    {
        if(input != -1)
            close(input);
    }
    if(data->fd[0] != -1)
        close(data->fd[0]);
    if(data->fd[1] != -1)
        close(data->fd[1]);
    if(data->envi)
      free_arr(data->envi);
    while(wait(&status) > 0);
}
