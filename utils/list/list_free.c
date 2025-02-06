
#include "../../header/minishell.h"

void	free_list(t_list **stack_to_free)
{
	t_list	*next_node;

	if (*stack_to_free == NULL)
		return ;
	while (*stack_to_free != NULL)
	{
		next_node = (*stack_to_free)->next;
		free(*stack_to_free);
		*stack_to_free = next_node;
	}
	*stack_to_free = NULL;
}
