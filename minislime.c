#include "minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


int count_cargs(t_cmd *cmd)
{
    int i;
    t_cmd *temp;

    i = 0;
    temp = cmd;
    while(temp->cargs[i])
    {  
            i++;
    }
    return (i);
}

// int count_args(t_toklist *list)
// {
//     int i;
//     t_toklist *temp;

//     i = 1;
//     temp = list;
//     while(temp && temp->type != PIPE)
//     {
//         // while(temp->type != PIPE)
//         // {
//         if(temp->type == FLAG || temp->type == ARGS)
//             i++;
//         //     temp=temp->next;
//         // }
//         // if(temp->type == PIPE)
//         //     break ;
//         temp = temp->next;
//     }
//     return (i);
// }

void check_built_in(char **av, t_shell *data)
{
    int i;

    i = 0;
    if (ft_strncmp(av[i], "exit", 5) == 0)
        exit_shell(av, data);
    else if(ft_strncmp(av[i], "env", 4) == 0)
        our_env(data->envir);
    else if(ft_strncmp(av[i], "unset", 6) == 0)
        our_unset(av[i + 1], &data->envir);
    else if(ft_strncmp(av[i], "echo", 5) == 0)
        our_echo(av);
    else if(ft_strncmp(av[i], "export", 7)== 0)
        our_export(av, data);
    else if(ft_strncmp(av[i], "pwd", 4) == 0)
    {
        if(av[i + 1] != NULL)
            write(2, "pwd: too many arguments\n", 24);
            //echo $?// data->exit_code = 1
        else    
            our_pwd();
    }
    else if(ft_strncmp(av[i], "cd", 3) == 0)
        our_cdir(av[i + 1], data);

}

void check_args(char **av, t_shell *data)
{
    // int i;

    // i = 0;
    check_built_in(av, data);

}
// strdup the content so when u unset you free and set to NULL
void init_shell(t_shell *data, char **envp)
{
    t_list *new_node;
    int i;

    //data->envi = envp;
    data->envi = NULL;
    data->envir = NULL;
    data->our_args = NULL;
    data->exit_code = 0;
    data->tokens= NULL;
    data->cmds = NULL;
    data->cmd_path = NULL;

    i = 0;
    if (envp)
    {   
        while(envp[i])
        {
            new_node = ft_lstnew(ft_strdup(envp[i]));
            if(!new_node)
            {
                write(2, "error malloc\n", 13);
                return ;
            }
            if(new_node)
                ft_lstadd_back(&data->envir, new_node);
            i++;
        }
    }
}

// int check_syntax(char **av, int i)
// {
//     i = 0;
//     while(av[i])
//     {
//         if(ft_strncmp(av[i], ">", 2) == 0 || ft_strncmp(av[i], "<", 2) == 0)
//         {
//             if(av[i + 1])
//             {
//                 if(ft_strncmp(av[i + 1], ">", 2) == 0 || ft_strncmp(av[i +1], "<", 2) == 0)
//                     {
//                         if(av[i + 2])
//                         {
//                             if(ft_strncmp(av[i + 2], ">", 2) == 0 || ft_strncmp(av[i + 2], "<", 2) == 0)
//                             {
//                                 write(2, "syntax error near unexpected token `>'\n", 39);
//                                 //exit code = 258 ?
//                                 return (1);
//                             }
//                         }
//                     }
//             }
//         }
//         i++;
//     }
//     return (0);
// }


int	check_syntax_redirect(char **av, int i)
{
	if (ft_strncmp(av[i + 1], ">", 2) == 0 || ft_strncmp(av[i + 1], "<",
			2) == 0  || ft_strncmp(av[i + 1], ">>", 3) == 0 || ft_strncmp(av[i + 1], "<<", 3) == 0)
	{
		// if (av[i + 2])
		// {
		// 	if (ft_strncmp(av[i + 2], ">", 2) == 0 || ft_strncmp(av[i + 2], "<",
		// 			2) == 0)
		// 	{
		// 		return (1);
		// 		// write(2, "syntax error near unexpected token `>'\n", 39);
		// 		// //exit code = 258 ?
		// 		// return (1);
		// 	}
		// }
        return (1);
	}
	return (0);
}
int check_syntax_pipe(char **av, int i)
{
    if(ft_strncmp(av[i + 1], "|", 2) == 0)
    {
        write(2, "syntax error near unexpected token `|'\n", 39);
        //exit code = 258
        return(1);
    }
    return(0);
}
int	check_syntax(char **av, int i)
{
	i = 0;
	while (av[i])
	{
        if(ft_strncmp(av[i], "|", 2) == 0)
        {
            if(av[i +1])
            {
                if(check_syntax_pipe(av, i) == 1)
                    return(1);
            }
            else
            {
                write(2, "syntax error near unexpected token `|'\n", 39);
                return(1);
            }

        }
		if (ft_strncmp(av[i], ">", 2) == 0 || ft_strncmp(av[i], "<", 2) == 0 || ft_strncmp(av[i], ">>", 3) == 0 || ft_strncmp(av[i], "<<", 3) == 0)
		{
			if (av[i + 1])
			{
				if (check_syntax_redirect(av, i) == 1)
				{
					write(2, "syntax error near unexpected token `>' or `<'\n", 46);
                    //data->exit_code = 258;
					return (1);
				}
			}
            else
            {
                write(2, "syntax error near unexpected token `newline'\n", 45);
                //data->exit_code = 258
                return (1);
            }
		}
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
    t_shell data;
    char *line;
    (void)ac;
    int i = 0;
    (void)envp;
    (void)av;
    //t_token *tokens;
    //int j = 0;
    t_toklist *tokens;
    // t_toklist *tmp;
    t_cmd *tmp;
    int count;

    init_shell(&data, envp);
    while(1)
    {
        i = 0;
        line = readline("minishell♣\n");
        // if(ft_strncmp(line, "exit", 4) == 0)
        // {
        //     free(line);
        //     exit(0);
        // }
        if(!line)
            exit(1);
        printf("\nbefore_trim - {%s}\n", line);
        av = our_tokenize(line);
        while(av[i])
        {
            printf("%d - [%s]\n", i + 1, av[i]);
            i++;
        }
        i--;
        //tokens = array_to_token_array(av, i);
        if(check_syntax(av, i) == 1)
        {
            free_arr(av);
            if(line)
                add_history(line);
            free(line);
            continue;
            printf("syntax\n");
            // free_arr(av);
        }
        else   
        {
            printf("else syntax\n");
            tokens = array_token_list(&data, av, i);
            //array_token_list(&data, av, i);
            // tmp = tokens;
            tokens = data.tokens;
            while(tokens)
            {
                printf("token: %s, type: %d\n", tokens->token, tokens->type);
                tokens = tokens->next;
            }
            // data.count = count_all_args(data.tokens);
            tmp = our_toklist_cmdlist(data.tokens, &data);
            //our_toklist_cmdlist(data.tokens, &data);
            // printf("args count: %d\n", count);
            int u = 0;
            while(tmp)
            {
                count = 0;
                count = count_cargs(tmp);
                printf("count: %d\n", count);
                u = 0;
                printf("cmd:%s ", tmp->cmd);
                while(u < count)
                    printf("args:%s ", tmp->cargs[u++]);
                printf("inf:%s, out:%s, limit:%s\n", tmp->inf, tmp->outf, tmp->limiter);
                tmp = tmp->next;
            }
        }
        // while(tokens[j].token)
        // {
        //     printf("hello\n");
        //     printf("token: %s, type:%d\n", (char *)tokens[j].token, (int)tokens[j].type);
        //     j++;
        // }
        //if(data.cmds)
            //our_execution(&data);
        if (av && av[0])
        {
            printf("before check_args\n");
            check_args(av, &data);
        }
        if(line)
            add_history(line);
        if (av)
        {
            free_arr(av);
        }
        // if (tokens)
        if (data.tokens)
            our_toklistclear(&data.tokens);
        if(data.cmds)
            our_cmdlistclear(&data.cmds);
        free(line);
        //we need clean everything before next line the allocations
    }
    return(0);
}

///// if (s[0] = -)
/// num= ft_atoi2(s)
//if 
//    dasdasd dsad s | " "      