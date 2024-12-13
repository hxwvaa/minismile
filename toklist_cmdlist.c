#include "minishell.h"

// void free_set_null(void **ptr)
// {
//     if(*ptr)
//     {
//         free(*ptr);
//         *ptr = NULL;
//     }
// }
void exit_free(t_shell *data)
{
    if(data->backup_pwd)
        free(data->backup_pwd); // can create a function that free and set to NULL, and we need to send & of our string// but since we exiting we dont need to
    if(data->cmds)
        our_cmdlistclear(&data->cmds);
    if(data->envir)
        our_envlistclear(&data->envir);
    if(data->tokens)    
        our_toklistclear(&data->tokens);
    //we need to free line as well so add line to our struct // or free it early on
    exit(errno);
}

t_cmd *our_clstlast(t_cmd *lst)
{
    t_cmd *ptr;

    if(!lst)
        return (NULL);
    ptr = lst;
    while(ptr->next != NULL)
        ptr = ptr->next;
    return(ptr);
}
int our_clstadd_back(t_cmd **lst, t_cmd *new)
{
    if(!new)
        return (-1);
    if(!*lst)
        *lst = new;
    else
        our_clstlast(*lst)->next = new;
    return (0);
}

t_redir *our_redirlast(t_redir *lst)
{
    t_redir *ptr;

    if(!lst)
        return (NULL);
    ptr = lst;
    while(ptr->next != NULL)
        ptr = ptr->next;
    return(ptr);
}

t_redir *our_redirnew(char *file, int flag)
{
    t_redir *new;

    new = ft_calloc(1, sizeof(t_redir));
    if(!new)
        return (NULL);
    new->file = ft_strdup(file);
    if(!new->file)
    {
        free(new);
        return(NULL);
    }
    new->hd_input = NULL;
    new->flag = flag;
    new->next = NULL;
    return(new);
}

int our_rediradd(t_redir **lst, char *file, int flag)
{
    t_redir *new;

    new = our_redirnew(file, flag);
    if(!new)
        return (-1);
    if(!*lst)
        *lst = new;
    else
        our_redirlast(*lst)->next = new;
    return (0);
}

t_cmd *our_clistnew(int count)
{
    t_cmd   *list;

    list = ft_calloc(1, sizeof(t_cmd));
    if(!list)
        return (NULL);
    list->cmd = NULL;
    list->cargs = ft_calloc((count + 1), sizeof(char *));
    if(!list->cargs)
        return (free(list), (NULL));
    list->cargs[0] = NULL;
    list->redirs = NULL;
    list->redir_out = 0;
    //list->em_expand =0
    //list->inputs = NULL;
   // list->outputs = NULL;
    list->next = NULL;
    return(list);
}

int count_args(t_toklist *list)
{
    int i;
    t_toklist *temp;

    i = 0;
    temp = list;
    while(temp && temp->type != PIPE)
    {
        if(temp->type == CMD || temp->type == FLAG || temp->type == ARGS)
            i++;
        temp = temp->next;
    }
    return (i);
}

t_cmd *new_node(t_toklist *temp, t_shell *data, int *new_cmd)
{
    t_cmd *new;
    new = our_clistnew(count_args(temp));
    if(!new)
    {
        perror("malloc");
        exit_free(data);
    }
    if(new)
    {
        if (our_clstadd_back(&data->cmds, new) == -1)
            exit_free(data);
    }
    *new_cmd = 0;
    return (new);
}

t_toklist *redirect_found(t_toklist *temp, t_cmd *curr, t_shell *data)
{
    int flag;

    if(temp->type == HERE_DOC)
        flag = 2;
    else if(temp->type == APPEND)
        flag = 1;
    else if(temp->type == REDIR_OUT)
        flag = 3;
    else
        flag = 0;
    temp = temp->next;
    if(temp && temp->token)
    {
        if (our_rediradd(&curr->redirs, temp->token, flag) == -1)
            exit_free(data);
    }
    return(temp);
}

int process_args(t_cmd *curr, t_toklist *temp, int i)
{
    curr->cargs[i] = ft_strdup(temp->token);
    if(!curr->cargs[i])
        return(-1);
    return(0);
}

int store_cmd(t_cmd *curr, t_toklist *temp)
{
    curr->cmd = ft_strdup(temp->token); // protect mallocs
    if(!curr->cmd)
        return(-1);
    curr->cargs[0] = ft_strdup(temp->token);
    if(!curr->cargs[0])
        return(-1);
    if(temp->em_ex)
        curr->em_expand = 1;
    return(0);
}
t_toklist *cmd_found_help(t_toklist *temp, t_cmd *curr, int j, t_shell *data)
{
    int i;

    i = 1;
    temp = temp->next;
    while(temp && temp->type != PIPE)
    {
        if((temp->type == CMD || temp->type == FLAG || temp->type == ARGS) 
            && !temp->em_ex && i <= j)
        {
            if(process_args(curr, temp, i++) == -1)
                exit_free(data);
        }
        if(temp->type == REDIR_IN || temp->type == REDIR_OUT 
            || temp->type == APPEND || temp->type == HERE_DOC)
            temp = redirect_found(temp, curr, data);
        temp = temp->next;
    }
    curr->cargs[i] = NULL;
    return(temp);
}
t_toklist *cmd_found(t_toklist *temp, t_cmd *curr, t_shell *data)
{
    int j;

    j = count_args(temp);
    if(temp->em_ex && temp->next)
        return (temp = temp->next);
    if(store_cmd(curr, temp) == -1)
        exit_free(data);
    temp = cmd_found_help(temp, curr, j, data);
    return(temp);
}

t_toklist *cmd_redirect(t_toklist *temp, t_cmd **curr, int *new_cmd, t_shell *data)
{
    if(temp->type == CMD)
        temp = cmd_found(temp, *curr, data);
    else if(temp->type == REDIR_IN || temp->type == REDIR_OUT 
        || temp->type == APPEND || temp->type == HERE_DOC)
        temp = redirect_found(temp, *curr, data);
    else if(temp->type == PIPE)
    {
        *new_cmd = 1;
        curr = NULL;
        temp= temp->next;
    }
    else
        temp = temp->next;
    return (temp);
}

t_cmd *our_toklist_cmdlist(t_toklist *list, t_shell *data)
{
    t_cmd *curr;
    t_toklist *temp;
    int new_cmd;

    curr = NULL;
    temp = list;
    new_cmd = 1;
    while(temp)
    {
        if(new_cmd == 1)
        {
            curr = new_node(temp, data, &new_cmd);
            if(!curr)
                return(perror("malloc"), NULL);
        }
        temp = cmd_redirect(temp, &curr, &new_cmd, data);
    }
    return(data->cmds);
}
