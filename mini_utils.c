#include "minishell.h"

// copilot did this lol, it looks like it should work
void free_all(t_shell *data)
{
    write (2, "\033[32;1mfree_all\n\033[0m", 21);
    if(data->envi)
        free_arr(data->envi);
    if(data->envir)
        our_envlistclear(&data->envir);
    if(data->our_args)
        free_arr(data->our_args);
    if(data->tokens)
        our_toklistclear(&data->tokens);
    if(data->cmds)
        our_cmdlistclear(&data->cmds);
    if(data->cmd_path)
        free(data->cmd_path);
    if(data->fd[0] != -1)
        close(data->fd[0]);
    if(data->fd[1] != -1)
        close(data->fd[1]);
    if(data->std[0] != -1)
        close(data->std[0]);
    if(data->std[1] != -1)
        close(data->std[1]);
}
