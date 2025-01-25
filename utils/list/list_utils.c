/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:26:31 by ofilloux          #+#    #+#             */
/*   Updated: 2025/01/25 12:08:35 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//Crea un nuevo nodo
t_tok_line	*ft_lst_new_node(void *content)
{
	t_tok_line	*new_node;

	new_node = malloc(sizeof(t_tok_line));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

//Crea un nuevo nodo y lo añade a la lista
// devuelve 1 si error, 0 si todo bien
// i_node es iterador nodo
int	add_to_list(t_tok_line **line, void *content)
{
	t_tok_line	*new_node;
	t_tok_line	*i_node;

	new_node = ft_lst_new_node(content);
	if (!new_node)
		return (free_node(line), 1); // A verificar luego si est necesario o relevente
									// hacer el free de toda la lista
									// si hay un error con el nuevo nodo
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

// devuelve el puntero hacia el útlimo nodo de la lista
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

//calcula el tamaño de la lista.
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

// añade el nodo "new" al final de la lista
void	ft_lstadd_back(t_tok_line **list, t_tok_line *new)
{
	t_tok_line	*temp;

	if (!*list)
		*list = new;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}
