#include "minishell.h"


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
void our_clstadd_back(t_cmd **lst, t_cmd *new)
{
    if(!new)
        return ;
    if(!*lst)
        *lst = new;
    else
        our_clstlast(*lst)->next = new;
}
// t_cmd *our_clistnew(char *cmd, int count)
// {
//     t_cmd   *list;

//     //list = malloc(sizeof(t_cmd));
//     list = ft_calloc(1, sizeof(t_cmd));
//     if(!list)
//         return (NULL);
//     list->cmd = ft_strdup(cmd);
//     if(!list->cmd)
//         return (free(list), (NULL));
//     //list->cargs = malloc((sizeof (char *)) * (count + 1));
//     list->cargs = ft_calloc((count + 1), sizeof(char *));
//     if(!list->cargs)
//         return (free(list->cmd), free(list), (NULL));
//     list->cargs[0] = ft_strdup(cmd);
//     if(!list->cargs[0])
//         return (free(list->cargs), free(list->cmd), free(list), NULL);
//     list->cargs[1] = NULL;
//     list->app = 0;
//     list->inf = NULL;
//     list->outf = NULL;
//     list->limiter = NULL;
//     list->hd_fd = -1;
//     list->next = NULL;
//     return(list);
// }


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
        return(free(new), NULL);
    new->hd_input = NULL;
    new->flag = flag;
    new->next = NULL;
    return(new);
}

void our_rediradd(t_redir **lst, char *file, int flag)
{
    t_redir *new;

    new = our_redirnew(file, flag);
    if(!new)
        return ;
    if(!*lst)
        *lst = new;
    else
        our_redirlast(*lst)->next = new;
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
        return (perror("malloc"), NULL);
    if(new)
        our_clstadd_back(&data->cmds, new);
    *new_cmd = 0;
    return (new);
}

t_toklist *redirect_found(t_toklist *temp, t_cmd *curr)
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
        our_rediradd(&curr->redirs, temp->token, flag);
    return(temp);
}

t_toklist *cmd_found(t_toklist *temp, t_cmd *curr)
{
    int i;
    int j;

    i = 1;
    j = count_args(temp);
    // if(!temp->token)
    // {
    //     curr->cmd = ft_strdup("''"); // not sure about this for case ""
    //     curr->cargs[0] = ft_strdup("''"); //not sure about this 
    // }
    // else
    // {
        // if(temp->em_ex) 
        // {
        //     curr->em_expand = 1;
        //     if(temp->next)
        //         return(temp = temp->next);
        // }
        if(temp->em_ex && temp->next)
            return (temp = temp->next);
        curr->cmd = ft_strdup(temp->token); // protect mallocs
        curr->cargs[0] = ft_strdup(temp->token);
        if(temp->em_ex)
            curr->em_expand = 1;
    //}
        temp = temp->next;
        while(temp && temp->type != PIPE)
        {
            if(temp->type == CMD || temp->type == FLAG || temp->type == ARGS)
            {
                if(!temp->em_ex)//to skip empty args
                {
                    if(i <= j)
                        curr->cargs[i++] = ft_strdup(temp->token);
                }
            }
            if(temp->type == REDIR_IN || temp->type == REDIR_OUT || temp->type == APPEND || temp->type == HERE_DOC)
                temp = redirect_found(temp, curr);
            temp = temp->next;
        }
        curr->cargs[i] = NULL;
        return(temp);
}

t_toklist *cmd_redirect(t_toklist *temp, t_cmd **curr, int *new_cmd)
{
    if(temp->type == CMD)
        temp = cmd_found(temp, *curr);
    else if(temp->type == REDIR_IN || temp->type == REDIR_OUT || temp->type == APPEND || temp->type == HERE_DOC)
        temp = redirect_found(temp, *curr);
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
        temp = cmd_redirect(temp, &curr, &new_cmd);
    }
    return(data->cmds);
}

//last working cmdlist, but redirect stored separate which wrong
// t_cmd *our_toklist_cmdlist(t_toklist *list, t_shell *data)
// {
//     int i;
//     t_cmd *new;
//     t_cmd *curr;
//     t_toklist *temp;

//     new = NULL;
//     curr = NULL;
//     //i = 1;
//     int j = 1;
//     temp = list;
//     while(temp)
//     {
//         if (j == 1)
//         {
//             new = our_clistnew(count_args(temp));
//             if(!new)
//                 return (perror("malloc"), NULL);
//             if(new)
//                 our_clstadd_back(&data->cmds, new);
//             curr = new;
//             j = 0;
//         }
//         if(temp->type == CMD)
//         {
 
//             curr->cmd = ft_strdup(temp->token); // protect mallocs
//             curr->cargs[0] = ft_strdup(temp->token);
//             i = 1;
//             int j = count_args(temp);
//             temp = temp->next;
//             while(temp && temp->type != PIPE)
//             {
//                 if(temp->type == CMD || temp->type == FLAG || temp->type == ARGS)
//                 {
//                     if(i <= j)
//                         curr->cargs[i++] = ft_strdup(temp->token);
//                 }
//                 if(temp->type == REDIR_IN || temp->type == HERE_DOC)
//                 {
//                     if(temp && temp->type == HERE_DOC)
//                     {
//                         temp = temp->next;
//                         our_rediradd(&curr->inputs, temp->token, 2);
//                     }
//                     else
//                     {
//                         temp = temp->next;
//                         our_rediradd(&curr->inputs, temp->token, 0);
//                     }
//                 }
//                 if(temp->type == REDIR_OUT || temp->type == APPEND)
//                 {
//                     if(temp && temp->type == APPEND)
//                     {
//                         temp = temp->next;
//                         our_rediradd(&curr->outputs, temp->token, 1);
//                     }
//                     else
//                     {
//                         temp = temp->next;
//                         our_rediradd(&curr->outputs, temp->token, 0);
//                     }
//                 }
//                 temp = temp->next;
//             }
//             curr->cargs[i] = NULL;    
//         }
//         else if(temp->type == REDIR_IN || temp->type == HERE_DOC)
//         {
//             if(temp && temp->type == HERE_DOC)
//             {
//                 temp = temp->next;
//                 our_rediradd(&curr->inputs, temp->token, 2);
//             }
//             else
//             {
//                 temp = temp->next;
//                 our_rediradd(&curr->inputs, temp->token, 0);
//             }
//         }
//         else if(temp->type == REDIR_OUT || temp->type == APPEND)
//         {
//             if(temp && temp->type == APPEND)
//             {
//                 temp = temp->next;
//                 our_rediradd(&curr->outputs, temp->token, 1);
//             }
//             else
//             {
//                 temp = temp->next;
//                 our_rediradd(&curr->outputs, temp->token, 0);
//             }
//         }
//         else if(temp->type == PIPE)
//         {
//             curr = NULL;
//             j = 1;
//             temp = temp->next;
//         }
//         else
//             temp = temp->next;
//     }
    
//     return(data->cmds);
// }



// //working code before
// t_cmd *our_toklist_cmdlist(t_toklist *list, t_shell *data)
// {
//     int i;
//     t_cmd *new;
//     t_cmd *curr;
//     t_toklist *temp;

//     new = NULL;
//     curr = NULL;
//     i = 0;
//     int j = 1;
//     temp = list;
//     while(temp)
//     {
//         if (j == 1)
//         {
//             new = clistnew(c_arg(temp), c_inf(temp), c_out(temp), c_lim(temp));
//             if(!new)
//                 return (perror("malloc"), NULL);
//             if(new)
//                 our_clstadd_back(&data->cmds, new);
//             curr = new;
//             j = 0;
//         }
//         if(temp->type == CMD)
//         {
//             //new = our_clistnew(temp->token, count_args(list));
//             //if(!new)
//                 //return (perror("malloc"), NULL);
//             // if(new)
//             //     our_clstadd_back(&data->cmds, new);
            
//             //curr = new;
//             curr->cmd = ft_strdup(temp->token); // protect mallocs
//             curr->cargs[0] = ft_strdup(temp->token);
//             i = 1;
//             int j = count_args(temp);
//             temp = temp->next;
//             while(temp && temp->type != PIPE)
//             {
//                 if(temp->type == CMD || temp->type == FLAG || temp->type == ARGS)
//                 {
//                     //memory leak if multiple redirection in command line ithink
//                     //eg.: asd > asd | asad >asdfdsd >agf 
//                     //idea for solution add enum for infile outfile & limiter,
//                     //and set token type when encountered
//                     if(i <= j)
//                         curr->cargs[i++] = ft_strdup(temp->token);
//                 //printf("dsf\n");
//                     //temp = temp->next;
//                 }
//                 if(temp->type == REDIR_IN || temp->type == HERE_DOC)
//                 {
//                     if(temp && temp->type == HERE_DOC)
//                     {
//                         temp = temp->next;
//                         int h = c_lim(temp);
//                         int hh = 0;
//                         if(hh <= h)
//                             curr->limiter[hh++] = ft_strdup(temp->token);
//                     }
//                     else
//                     {
//                         temp = temp->next;
//                         int in = c_inf(temp);
//                         int inn = 0;
//                         if(inn <= in)
//                             curr->inf[inn++] = ft_strdup(temp->token);
//                     }
//                 }
//                 if(temp->type == REDIR_OUT || temp->type == APPEND)
//                 {
//                     int aa = c_out(temp);
//                     int ac = 0;
//                     if(temp && temp->type == APPEND)
//                     {
//                         temp = temp->next;
//                         curr->app = 1;
//                         if(ac <= aa)
//                             curr->outf[ac++] = ft_strdup(temp->token);
//                     }
//                     else
//                     {
//                         temp = temp->next;
//                         curr->app = 0;
//                             curr->outf[ac++] = ft_strdup(temp->token);
//                     }
//                 }
//                 temp = temp->next;
//             }
//             curr->cargs[i] = NULL;
//         }
//         else if(temp->type == REDIR_IN || temp->type == HERE_DOC)
//         {
//             if(temp && temp->type == HERE_DOC)
//             {
//                 temp = temp->next;
//                 curr->limiter = ft_strdup(temp->token);
//             }
//             else
//             {
//                 temp = temp->next;
//                 curr->inf = ft_strdup(temp->token);
//             }
//         }
//         else if(temp->type == REDIR_OUT || temp->type == APPEND)
//         {
//             if(temp && temp->type == APPEND)
//             {
//                 temp = temp->next;
//                 curr->outf = ft_strdup(temp->token);
//                 curr->app = 1;
//             }
//             else
//             {
//                 temp = temp->next;
//                 curr->outf = ft_strdup(temp->token);
//                 curr->app = 0;
//             }
//         }
//         else if(temp->type == PIPE)
//         {
//             curr = NULL;
//             j = 1;
//             temp = temp->next;
//         }
//         else
//             temp = temp->next;
//     }
//     return(data->cmds);
// }
