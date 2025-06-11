/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:26:31 by ofilloux          #+#    #+#             */
/*   Updated: 2025/05/11 18:48:49 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

//Crea un nuevo nodo
t_dlist	*ft_lst_new_node(void *content)
{
	t_dlist	*new_node;

	new_node = malloc(sizeof(t_dlist));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

//Crea un nuevo nodo y lo añade a la lista
// devuelve 1 si error, 0 si todo bien
// i_node es iterador nodo
int	add_to_list(t_dlist **list, void *content)
{
	t_dlist	*new_node;
	t_dlist	*i_node;

	if (!content)
		return (1);
	new_node = ft_lst_new_node(content);
	if (!new_node)
		return (free_list1(list), 1); // A verificar luego si est necesario o relevente
									// hacer el free de toda la lista
									// si hay un error con el nuevo nodo
	if (*list == NULL)
	{
		*list = new_node;
		new_node->prev = NULL;
	}
	else
	{
		i_node = *list;
		while (i_node->next != NULL)
			i_node = i_node->next;
		new_node->prev = i_node;
		i_node->next = new_node;
	}
	return (0);
}

// devuelve el puntero hacia el útlimo nodo de la lista
t_dlist	*find_last_d_node(t_dlist **lst)
{
	t_dlist	*tmp;

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
long	stack_lenght(t_dlist **list)
{
	t_dlist	*tmp;
	long	i;

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
void	ft_d_lstadd_back(t_dlist **list, t_dlist *new)
{
	t_dlist	*temp;

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
