/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:48:18 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 16:06:09 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	myenv(t_col *col)
{
	int i;

	i = 0;
	while (col->env[i])
	{
		write(1, col->env[i], ft_strlen(col->env[i]));
		write(1, "\n", 1);
		i++;
	}
	g_error = 0;
}
