/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:44:34 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 15:45:23 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mypwd(void)
{
	char *dir;

	dir = getcwd(NULL, 0);
	if (dir == NULL)
		exit(1);
	write(1, dir, strlen(dir));
	write(1, "\n", 1);
	free(dir);
	g_error = 0;
}
