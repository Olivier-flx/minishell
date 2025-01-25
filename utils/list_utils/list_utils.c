/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:26:31 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/25 11:41:09 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_tok_line	*ft_lst_new_node(t_tok_line **new_node)
{
	t_tok_line	*new;

	new = malloc(sizeof(t_tok_line));
	if (!new)
	{
		free_stacks(new_node);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

int	add_to_list(t_tok_line **line)
{
	t_tok_line	*new_node;
	t_tok_line	*i_node;

	new_node = ft_lst_new_node(new_node);
	if (!new_node)
		return (1);
	if (*line == NULL)
	{
		*line = new_node;
		new_node->prev = NULL;
	}
	else
	{
		i_node = *line;
		while (i_node->next != NULL)
			i_node = i_node->next;
		new_node->prev = i_node;
		i_node->next = new_node;
	}
	return (0);
}

t_tok_line	*find_last_node(t_tok_line **lst)
{
	t_tok_line	*tmp;

	tmp = *(lst);
	if (!(*lst) || !lst)
		return (NULL);
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

long	stack_lenght(t_tok_line **list)
{
	t_tok_line	*tmp;
	long		i;

	if (!(*list))
		return (0);
	tmp = *list;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_back(t_tok_line **lst, t_tok_line *new)
{
	t_tok_line	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}
