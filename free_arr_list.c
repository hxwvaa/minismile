/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:31:37 by mshaheen          #+#    #+#             */
/*   Updated: 2024/11/07 13:07:26 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	// if (!*arr || !arr)
	// 	return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}


void	our_envlistclear(t_list **envir)
{
	t_list	*temp;

	while (*envir != NULL)
	{
		temp = (*envir)->next;
		free((*envir)->content);
		free(*envir);
		*envir = temp;
	}
	*envir = NULL;
	//printf("hi\n");
}

void	our_toklistclear(t_toklist **tokens)
{
	t_toklist	*temp;

	while (*tokens != NULL)
	{
		temp = (*tokens)->next;
		free((*tokens)->token);
		(*tokens)->token = NULL;
		free(*tokens);
		*tokens = NULL;
		*tokens = temp;
	}
	*tokens = NULL;
	//printf("wow\n");
}

void our_redirclear(t_redir **list)
{
	t_redir *temp;

	while(*list != NULL)
	{
		temp = (*list)->next;
		if((*list)->file)
		{
			free((*list)->file);
			(*list)->file = NULL;
		}
		if((*list)->hd_input)
		{
			free((*list)->hd_input);
			(*list)->hd_input = NULL;
		}
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

void	our_cmdlistclear(t_cmd **list)
{
	t_cmd	*tmp;

	while (*list != NULL)
	{
		tmp = (*list)->next;
		if ((*list)->cmd)
			free((*list)->cmd);
		(*list)->cmd = NULL;
		if ((*list)->cargs)
			free_arr((*list)->cargs);
		if((*list)->redirs)
			our_redirclear(&(*list)->redirs);
		// if((*list)->inputs)
		// 	our_redirclear(&(*list)->inputs);
		// if((*list)->outputs)
		// 	our_redirclear(&(*list)->outputs);
		free(*list);
		(*list) = tmp;
	}
	*list = NULL;
	//printf("cmdlist free\n");
}
