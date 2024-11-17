#include "minishell.h"

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

int only_one_cmd(t_cmd *cmd) // change this function
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

void invalid_lstcmd(char *file, int *input, int *output, t_shell *data)
{
    write(2, "minishell: command not found: ", 30);
    ft_putstr_fd(file, 2);
    write(2, "\n", 1);
	//ft_putendl_fd(file, 2);
	//free_array(array);
    if(*input != -1)
	    close(*input);
    if(*output != -1)
	    close(*output);
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
    write(2, "inside execute builtin\n", 23);
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
        // if(curr->cargs[i + 1] != NULL)
        //     write(2, "pwd: too many arguments\n", 24);
            //echo $?// data->exit_code = 1
        //else    
            j = our_pwd();
    }
    else if(ft_strncmp(curr->cmd, "cd", 3) == 0)
    {
        write(2, "before cd\n", 10);
        printf("before cd\n");
        our_cdir(curr->cargs[i + 1], data);
        printf("after cd\n");
    }
    return(j);
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

int input_file(t_cmd *curr, int *input)
{
    if(*input != STDIN_FILENO && *input != -1)
    {
        close(*input);
        *input = -1;
    }
    if(curr->hd_input)
    {
        int hdpipe[2];

        if(*input != STDIN_FILENO && *input != -1)
            close(*input);
        pipe(hdpipe);
        write(hdpipe[1], curr->hd_input, ft_strlen(curr->hd_input));
        close(hdpipe[1]);
        //input = hdpipe[0];
        free(curr->hd_input);
        curr->hd_input = NULL;
        *input = hdpipe[0];
        //return (hdpipe[0]);
        return (0);
    }
    if(curr->inf) // else
    {
        *input = open(curr->inf, O_RDONLY, 0777);
        if(*input == -1)
        {
            input_invalid(curr->inf);
            //input = open("/dev/null", O_RDONLY);
            int pipefd[2];
            pipe(pipefd);
            close(pipefd[1]);
            *input = pipefd[0];
            return (-1);
            //without this it would make the program hang cause it waits for input
            // mycommand line is < asd cat | wc -l, it will run forever because wc -l waits for
            // input
            //return (-1);
        }
    }
    //return (input);
    return (0);
}
void set_redirection(t_cmd *curr, t_shell *data, int *input, int *output)
{
    if(*input != STDIN_FILENO && *input != -1)
    {
        dup2(*input, STDIN_FILENO);
        close(*input);
    }
    // if(curr->next)
    // {
    //     dup2(data->fd[1], STDOUT_FILENO);
    //     if(data->fd[1] != -1)
    //         close(data->fd[1]);
    //     if(data->fd[0] != -1)
    //         close(data->fd[0]);
    // }
    if(curr->next && data->fd[1] != -1)
    {
        printf("inside stdout\n");
        if(dup2(data->fd[1], STDOUT_FILENO) == -1)
            write(2, "error dup2\n", 11);
        if(data->fd[1] != -1)    
            close(data->fd[1]);
        //close(data->fd[0]);
        data->fd[1] = -1;
        // if(data->fd[0] != -1)
        //     close(data->fd[0]); // this causing sigpipe but if remove it i have fd leak
        // data->fd[0] = -1;
    }
    if(curr->outf)
    {
        if(curr->app)
            *output = open(curr->outf, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            *output = open(curr->outf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(*output == -1)
            output_invalid(curr->outf, data->fd[0], data);
        if (*output != STDOUT_FILENO)
        {
            dup2(*output, STDOUT_FILENO);
            close(*output);
        }
    }
}

void builtin_pipeline(t_cmd *curr, t_shell *data)
{
    //execute_one_cmd(curr, data);
    int r;
    
    r = execute_one_cmd(curr, data);
    if(r == 0) 
    {
        //printf("inside r\n");
        if(data->envir)
            our_envlistclear(&data->envir);
        if(data->cmds) 
            our_cmdlistclear(&data->cmds);
        if(data->envi)
            free_arr(data->envi);
        close(data->fd[0]); // to close read end after writing to the pipe
        exit(0);
    }
    printf("outside r\n");
    if(data->envir)
        our_envlistclear(&data->envir);
    if(data->cmds) 
        our_cmdlistclear(&data->cmds);
    if(data->envi)
        free_arr(data->envi);
    close(data->fd[0]);
    exit(1);
}

// void handle_sigpipe(int sig)
// {
//     (void)sig;
// }

void execute_child(t_shell *data, t_cmd *curr, int *input, int *output)
{
    //signal(SIGPIPE, handle_sigpipe);
    set_redirection(curr, data, input, output);
    if(curr->cmd)
    {
        if (is_builtin(curr->cmd))
            builtin_pipeline(curr, data); 
        if(data->fd[0] != -1)    
            close(data->fd[0]);// not needed ? //sigpipe signal 13 is non-builtin | < Makefile wc -l // if i dont add it fd leaks
        data->cmd_path = get_cmd_path(curr->cmd, data->envi);
        if (!data->cmd_path)
            invalid_lstcmd(curr->cmd, input, output, data);
        //printf("cmd_path: %s\n", data->cmd_path);
        if (execve(data->cmd_path, curr->cargs, data->envi) == -1) // if it fails even  though it is a valid command maybe because i malloc more space??
            invalid_lstcmd(curr->cmd, input, output, data); // dont forget to free data->envi, and change exit_code var 127
    }
    write(2, "before closing and cleaning\n", 28);
    if(*input != -1)
	    close(*input);
    if(*output != -1)
	    close(*output);
    close(data->fd[0]); // if there is no cmd i need to close it or i get fd leak
    //close(data->fd[0]); // maybe i dont need this aswell
    if(data->envir)
        our_envlistclear(&data->envir);
    if(data->cmds) 
        our_cmdlistclear(&data->cmds);
    if(data->envi)
        free_arr(data->envi);
    data->exit_code = 0;
    //exit_shell(data->cmds->cargs, data);
	exit(0);
}

void prepare_fds(int *input, int *output, t_shell *data, t_cmd *curr)
{
    if(*input != STDIN_FILENO)
    {
        if(*input != -1) 
            close(*input);
    }
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
    if(*output != STDOUT_FILENO)
    {
        if(*output != -1)
            close(*output);
    }
}
void close_clean(t_shell *data, int input, int output)
{
    if(input != STDIN_FILENO)
    {
        if(input != -1)
            close(input);
    }
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

void fork_execute_child(t_shell *data, t_cmd *curr, int *input, int *output)
{
    data->pid = fork();
    if(data->pid == -1)
        perror("fork");
    if(data->pid == 0)
        execute_child(data, curr, input, output);
}
//before calling the function initialize data->envi
//when calling the function, pass STDIN_FILENO and -1
void execution(t_shell *data, int input, int output)
{
    t_cmd *curr;
    int status;

    process_heredoc(data->cmds);
    curr = data->cmds;
    // data->fd[0] = -1;
    // data->fd[1] = -1; i already initialize it in init shell
    while(curr)
    {
        if(curr->inf || curr->hd_input)
        {
            //input = input_file(curr, input);
            // int j;
            // j = input_file(curr, &input);
            if(input_file(curr, &input) == -1)
            {
                curr = curr->next;
                continue ;
            }
        }
        if(curr->next && pipe(data->fd) == -1)
        {   
            perror("pipe");
           // fork_execute_child(data, curr, &input, &output);
        }
        if(is_builtin(curr->cmd) && only_one_cmd(data->cmds) == 1) //need to change the if statement < Makefile cat | << lol > result.txt | pwd | <<world >> result.txt
            execute_one_cmd(curr, data);
        else
            fork_execute_child(data, curr, &input, &output);
        prepare_fds(&input, &output, data, curr);
        curr = curr->next;
    }
    close_clean(data, input, output);
    while(wait(&status) > 0);
}
