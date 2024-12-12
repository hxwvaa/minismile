#include "minishell.h"

// copilot did this lol, it looks like it should work
void free_all(t_shell *data)
{
    write (2, "\033[32;1mfree_all\n\033[0m", 21);
    if(data->envi)
    {
        free_arr(data->envi);
        data->envi = NULL;
    }
    if(data->envir)
    {
        our_envlistclear(&data->envir);
        data->envir = NULL;
    }
    if(data->our_args)
    {
        write(2, "freeing our_args\n", 17);
        free_arr(data->our_args);
        data->our_args = NULL;
    }
    if(data->tokens)
    {
        write(2, "freeing tokens\n", 15);
        our_toklistclear(&data->tokens);
        data->tokens = NULL;
    }
    if(data->cmds)
    {
        write(2, "freeing cmds\n", 13);
        our_cmdlistclear(&data->cmds);
        data->cmds = NULL;
    }
    if(data->cmd_path)
    {
        write(2, "freeing cmd_path\n", 18);
        free(data->cmd_path);
        data->cmd_path = NULL;
    }
    if (data->backup_pwd)
    {
        write(2, "freeing backup_pwd\n", 20);
        free(data->backup_pwd);
        data->backup_pwd = NULL;
    }
    if(data->fd[0] != -1)
    {
        write(2, "closing fd[0]\n", 15);
        close(data->fd[0]);
        data->fd[0] = -1;
    }
    if(data->fd[1] != -1)
    {
        write(2, "closing fd[1]\n", 15);
        close(data->fd[1]);
        data->fd[1] = -1;
    }
    if(data->std[0] != -1)
    {
        write(2, "closing std[0]\n", 16);
        close(data->std[0]);
        data->std[0] = -1;
    }
    if(data->std[1] != -1)
    {
        write(2, "closing std[1]\n", 16);
        close(data->std[1]);
        data->std[1] = -1;
    }
}
