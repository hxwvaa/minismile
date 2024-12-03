#include "../minishell.h"


int opened_or_closed(char *str)
{
    int i;
    char quote;

    i = 0;
    quote = 0;
    while(str[i])
    {
        if(str[i] == '\'' || str[i] == '\"')
        {
            if(quote == 0)
                quote = str[i];
            else if(quote == str[i])
                quote = 0;
        }
        i++;
    }
    if (quote != 0)
        return (quote);
    return (0);
}

int check_quotes(t_toklist *list)
{
    t_toklist *temp;
    char quote;

    temp = list;
    quote = 0;
    while(temp)
    {
        quote= opened_or_closed(temp->token);
        if(quote != 0)
        {
            if(quote == '\'')
                ft_putendl_fd("syntax error unclosed quote \'", 2);
            else
                ft_putendl_fd("syntax error unclosed quote \"", 2);
            return (-1);
        }
        temp = temp->next;
    }
    return(0);
}
