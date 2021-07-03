/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shlvl2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:41:14 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 12:43:11 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*try_iter_shlvl(char *str)
{
	int		d;
	char	*c;

	d = ft_atoi(str);
	d++;
	if (d > 1000)
	{
		write(1, "warning: shell level (", 22);
		write(1, ft_itoa(d), ft_strlen(ft_itoa(d)));
		write(1, ") too high, resetting to 1\n", 27);
		d = 1;
	}
	if (d < 0)
		d = 0;
	c = ft_itoa(d);
	if (c == NULL)
		exit(1);
	return (c);
}
