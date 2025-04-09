/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:51:49 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/09 19:47:39 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	print_dlist(t_dlist **list)
{
	t_dlist	*i_node;
	//char	*to_print;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!list)
		return ;
	i_node = *list;
	while (i_node)
	{
		if (i_node->content)
		{
			printf("chunk numero %i = ", j);
			j++;
			fflush(stdout);
			i = 0;
			while (((t_chunk *)i_node->content)->content[i])
			{
				printf("`%s`;", ((t_chunk *)i_node->content)->content[i++]);
				fflush(stdout);
			}
			printf("\n");
			fflush(stdout);
		}
		//else
		//	printf("Error: content is NULL in node.\n");
		i_node = i_node->next;
	}
}


// @debug : Funccion que imprime la lista de comandos entera y imprime el contenido de cada nodo
void debug_print_cmd_list(t_dlist **cmd_list_ptr)
{
    t_dlist *cmd_list = *cmd_list_ptr;
    t_dlist *current = cmd_list;
    int index = 0;

    printf("\n--- Début de l'affichage de cmd_list ---\n");

    if (current == NULL)
    {
        printf("La liste cmd_list est NULL ou vide.\n");
    }
    else
    {
        while (current != NULL)
        {
            printf("Nœud [%d]:\n", index);
            if (current->content == NULL)
            {
                printf("  content: NULL\n");
            }
            else
            {
                t_chunk *chunk = (t_chunk *)current->content;
                printf("  content (t_chunk):\n");
                if (chunk->content == NULL)
                {
                    printf("    chunk->content: NULL\n");
                }
                else
                {
                    printf("    chunk->content:\n");
                    for (int i = 0; chunk->content[i] != NULL; i++)
                    {
                        printf("      [%d]: \"%s\"\n", i, chunk->content[i]);
                    }
                    printf("      [%d]: NULL (fin du tableau)\n", pp_char_len(chunk->content));
                }
                printf("    chunk->type: %d\n", chunk->type);
                printf("    chunk->has_redir: %s\n", chunk->has_redir ? "true" : "false");
                printf("    chunk->redir_count: %d\n", chunk->redir_count);
                // Vous pouvez ajouter l'affichage d'autres membres de t_chunk si nécessaire
            }
            current = current->next;
            index++;
        }
    }

    printf("--- Fin de l'affichage de cmd_list ---\n\n");
}
