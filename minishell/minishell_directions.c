/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_directions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:44:45 by sglass            #+#    #+#             */
/*   Updated: 2021/03/09 00:37:22 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	direction(t_all all, t_col *col)
{
	int flag;

	flag = 0;
	g_sig = 1;
	g_quit = 1;
	roll_parts(all, col);
	g_quit = 0;
	g_sig = 0;
}

void	roll_parts(t_all all, t_col *col)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (all.cmd_count != 1 && all.cmd[0].name != 0 && all.cmd[0].name[0] != 0)
		roll_commands(all, col);
	else if (all.cmd_count == 1 && all.cmd[0].name != 0 &&
	all.cmd[0].name[0] != 0)
		roll_commands2(all, col);
}

void	roll_commands2(t_all all, t_col *col)
{
	int i;

	i = 0;
	while (i < all.cmd_count && all.cmd->name != 0)
	{
		if (all.cmd[i].fd[0] != -1 && all.cmd[i].rd[0] != -1)
			sorter1(all.cmd[i], col);
		i++;
	}
}
