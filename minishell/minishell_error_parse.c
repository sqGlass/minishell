/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_parse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:39:41 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 19:40:08 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		er(char *s)
{
	ft_putstr_fd(s, 2);
	write(2, "\n", 1);
	g_error = 258;
	return (-1);
}

int		line_error_count(char *line)
{
	int		i;
	char	*error;

	i = 0;
	if ((error = ft_itoa(g_error)) == 0)
		return (0);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?' && line[i - 1] != -4)
			i += ft_strlen(error);
		else
			i++;
	}
	free(error);
	return (i);
}

int		result_redact(char *res)
{
	char	*error;
	int		i;

	if ((error = ft_itoa(g_error)) == 0)
		return (0);
	i = -1;
	while (error[++i])
		res[i] = error[i];
	free(error);
	return (i);
}

char	*error_parse(char *line)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if ((res = ft_calloc(line_error_count(line) + 1, sizeof(char))) == 0)
		return (0);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?' && line[i - 1] != -4)
		{
			i += 2;
			j += result_redact(&res[j]);
		}
		else
			res[j++] = line[i++];
	}
	free(line);
	return (res);
}
