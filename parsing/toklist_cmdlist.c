/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toklist_cmdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:40:29 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/15 23:40:29 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void free_set_null(void **ptr)
// {
//     if(*ptr)
//     {
//         free(*ptr);
//         *ptr = NULL;
//     }
// }

t_toklist	*redirect_found(t_toklist *temp, t_cmd *curr, t_shell *data)
{
	int	flag;

	if (temp->type == HERE_DOC)
		flag = 2;
	else if (temp->type == APPEND)
		flag = 1;
	else if (temp->type == REDIR_OUT)
		flag = 3;
	else
		flag = 0;
	temp = temp->next;
	if (temp && temp->token)
	{
		if (our_rediradd(&curr->redirs, temp->token, flag) == -1)
			exit_free(data);
	}
	return (temp);
}

t_toklist	*cmd_found_help(t_toklist *temp, t_cmd *curr, int j, t_shell *data)
{
	int	i;

	i = 1;
	temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		if ((temp->type == CMD || temp->type == FLAG || temp->type == ARGS)
			&& !temp->em_ex && i <= j)
		{
			if (process_args(curr, temp, i++) == -1)
				exit_free(data);
		}
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == APPEND || temp->type == HERE_DOC)
			temp = redirect_found(temp, curr, data);
		temp = temp->next;
	}
	curr->cargs[i] = NULL;
	return (temp);
}

t_toklist	*cmd_found(t_toklist *temp, t_cmd *curr, t_shell *data)
{
	int	j;

	j = count_args(temp);
	if (temp->em_ex && temp->next)
		return (temp = temp->next);
	if (store_cmd(curr, temp) == -1)
		exit_free(data);
	temp = cmd_found_help(temp, curr, j, data);
	return (temp);
}

t_toklist	*cmd_redirect(t_toklist *temp, t_cmd **curr,
	int *new_cmd, t_shell *data)
{
	if (temp->type == CMD)
		temp = cmd_found(temp, *curr, data);
	else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
		|| temp->type == APPEND || temp->type == HERE_DOC)
		temp = redirect_found(temp, *curr, data);
	else if (temp->type == PIPE)
	{
		*new_cmd = 1;
		curr = NULL;
		temp = temp->next;
	}
	else
		temp = temp->next;
	return (temp);
}

t_cmd	*our_toklist_cmdlist(t_toklist *list, t_shell *data)
{
	t_cmd		*curr;
	t_toklist	*temp;
	int			new_cmd;

	curr = NULL;
	temp = list;
	new_cmd = 1;
	while (temp)
	{
		if (new_cmd == 1)
		{
			curr = new_node(temp, data, &new_cmd);
			if (!curr)
				return (perror("malloc"), NULL);
		}
		temp = cmd_redirect(temp, &curr, &new_cmd, data);
	}
	return (data->cmds);
}
