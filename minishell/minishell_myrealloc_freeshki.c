/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_myrealloc_freeshki.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:33:24 by sglass            #+#    #+#             */
/*   Updated: 2021/03/08 16:36:26 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	freesh(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

char	**myrealloc(char **arr)
{
	int		i;
	char	**newar;

	i = 0;
	while (arr[i])
		i++;
	newar = ft_calloc(i + 2, sizeof(char *));
	if (newar == NULL)
		exit(1);
	i = 0;
	while (arr[i])
	{
		if ((newar[i] = ft_strdup(arr[i])) == 0)
			exit(1);
		free(arr[i]);
		i++;
	}
	free(arr);
	return (newar);
}

int		count_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	fre(t_col *col)
{
	int i;

	i = 0;
	while (col->exp[i])
	{
		free(col->exp[i]);
		i++;
	}
	free(col->exp);
}
