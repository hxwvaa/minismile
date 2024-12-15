/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:38:17 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/16 00:41:07 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_toklist *list)
{
	int			i;
	t_toklist	*temp;

	i = 0;
	temp = list;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMD || temp->type == FLAG || temp->type == ARGS)
			i++;
		temp = temp->next;
	}
	return (i);
}

int	process_args(t_cmd *curr, t_toklist *temp, int i)
{
	curr->cargs[i] = ft_strdup(temp->token);
	if (!curr->cargs[i])
		return (-1);
	return (0);
}

int	store_cmd(t_cmd *curr, t_toklist *temp)
{
	curr->cmd = ft_strdup(temp->token);
	if (!curr->cmd)
		return (-1);
	curr->cargs[0] = ft_strdup(temp->token);
	if (!curr->cargs[0])
		return (-1);
	if (temp->em_ex)
		curr->em_expand = 1;
	return (0);
}

void	exit_free(t_shell *data)
{
	if (data->backup_pwd)
		free(data->backup_pwd);
	if (data->cmds)
		our_cmdlistclear(&data->cmds);
	if (data->envir)
		our_envlistclear(&data->envir);
	if (data->tokens)
		our_toklistclear(&data->tokens);
	//we need to free line as well so add line to our struct
	exit(errno);
}

t_cmd	*new_node(t_toklist *temp, t_shell *data, int *new_cmd)
{
	t_cmd	*new;

	new = our_clistnew(count_args(temp));
	if (!new)
	{
		perror("malloc");
		exit_free(data);
	}
	if (new)
	{
		if (our_clstadd_back(&data->cmds, new) == -1)
			exit_free(data);
	}
	*new_cmd = 0;
	return (new);
}
