#include "../minishell.h"

char *expand_what(char *line, int start, int *len)
{
	char *to_expand;
	int i;

	i = start;
	while(line[i] && line[i] != 32 && !(line[i] >= 9 && line[i] <= 13) && line[i] != '\"' && line[i] != '\'' && line[i] != '$')
		i++;
	*len = i;
	to_expand = ft_substr(line, start, i - start);
	if(!to_expand)
		return(perror("malloc"), NULL);
	return(to_expand);
}

char *join_strs(char *s1, char *s2, char *line)
{
	char *temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if(!temp)
		return(perror("malloc"), free(line), NULL);
	return (temp);
}
int append_input(char **input, char *line)
{
	char *temp;
	char *new_line;
	new_line = ft_strjoin(line, "\n");
	if(!new_line)
		return(perror("malloc"), -1);
	temp = ft_strjoin(*input, new_line);
	free(new_line);
	if(!temp)
		return(perror("malloc"), -1);
	free(*input);
	*input = temp;
	return(0);
}
