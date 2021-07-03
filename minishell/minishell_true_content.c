/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_true_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:41:02 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 19:42:23 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		reveal_magic(char *arg, int f, int g, char *str)
{
	while (arg[f] == -5 ||
	arg[f] == -6 || arg[f] == -4)
		f++;
	if (arg[f] == -1)
		str[g++] = ' ';
	else if (arg[f] == -2)
		str[g++] = '|';
	else if (arg[f] == -3)
		str[g++] = ';';
	else if (arg[f] == -7)
		str[g++] = 92;
	else if (arg[f] == -10)
		str[g++] = '$';
	else
		str[g++] = arg[f];
	f++;
	return (f);
}

char	*true_content(t_all *all, int i, int j, int z)
{
	int		f;
	int		g;
	char	*str;

	f = 0;
	g = 0;
	if ((str = ft_calloc(ft_strlen(all[i].cmd[j].arg[z]) + 1,
		sizeof(char))) == 0)
		return (0);
	while (all[i].cmd[j].arg[z][f])
	{
		f = reveal_magic(all[i].cmd[j].arg[z], f, g, &str[0]);
		g++;
	}
	free(all[i].cmd[j].arg[z]);
	return (str);
}
