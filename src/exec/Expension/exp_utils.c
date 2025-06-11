/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:21:48 by ofilloux          #+#    #+#             */
/*   Updated: 2025/06/08 09:23:03 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	handle_expension(t_data *data, char **var_name, char *expd_token_j)
{
	char	*var_value;
	int		copied_len;

	copied_len = 0;
	var_value = ft_getenv(data->env_list, *var_name);
	if (ft_strcmp(*var_name, "?") == 0)
		var_value = ft_itoa(data->exit_status);
	if (var_value)
		copied_len = ft_strlcpy(expd_token_j, var_value, \
			ft_strlen(var_value) + 1);
	else
		copied_len = ft_strlcpy(expd_token_j, "", 2);
	if (ft_strcmp(*var_name, "?") == 0)
		ft_free((void **) &var_value);
	ft_free((void **) var_name);
	return (copied_len);
}

//V1
/* static int	handle_expension(t_data *data,
	char **var_name, char *expd_token_j)
{
	char	*var_value;
	int		copied_len;

	copied_len = 0;
	var_value = ft_getenv(data->env_list, *var_name);
	if (ft_strcmp(*var_name, "?") == 0)
		var_value = ft_itoa(data->exit_status);
	if (var_value)
		copied_len = ft_strlcpy(expd_token_j, var_value,
			ft_strlen(var_value) + 1);
	// else if (!var_value && )
	// 	copied_len = ft_strlcpy(expd_token_j, "$", 2);
	else
		copied_len = ft_strlcpy(expd_token_j, "", 2);
	if (ft_strcmp(*var_name, "?") == 0)
		ft_free((void **) &var_value);
	ft_free((void **) var_name);
	return (copied_len);
} */

void	increment_i_expension_loop(char *var_name, char *str, int	*i)
{
	int	var_name_len;

	var_name_len = 0;
	var_name_len = ft_strlen(var_name);
	if (str[(*i) + 1] && str[(*i) + 1] == '{')
		(*i) += var_name_len + 3;
	else
		(*i) += var_name_len + 1;
}

void	init_i_j(int *i, int *j)
{
	*i = 0;
	*j = 0;
}
