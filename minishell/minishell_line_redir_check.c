/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_line_redir_check.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:44:11 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/08 17:41:10 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			line_check(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[0] == '\0')
			return (-1);
		if (line[0] == '(')
			return (er("minishel: syntax error near unexpected token `('"));
		if (line[0] == ')')
			return (er("minishel: syntax error near unexpected token `)'"));
		if (line[0] == ';')
			return (er("minishel: syntax error near unexpected token `;'"));
		if (line[0] == '|')
			return (er("minishel: syntax error near unexpected token `|'"));
		if (line[i] == ';' && line[i + 1] == ';')
			return (er("minishel: syntax error near unexpected token `;;'"));
		if (line[0] == '|' && line[1] == '|')
			return (er("minishel: syntax error near unexpected token `||'"));
		if (line[i] == '|' && line[i + 1] == '|')
			return (er("minishel: bonus part"));
		if (line[i] == '|' && line[i + 1] == '\0')
			return (er("multiline command."));
	}
	return (0);
}

static int	redir_check3(char *line, int j)
{
	if (line[j] == '<')
		return (er("minishel: too many tokens detected '<'"));
	while (line[j] == ' ')
		j++;
	if (line[j] == '<')
		return (er("minishel: syntax error near unexpected token `<'"));
	if (line[j] == '\0')
		return (er("minishel: syntax error near unexpected token `newline'"));
	if (line[j] == '&')
		return (er("minishel: syntax error near unexpected token `&'"));
	if (line[j] == ';')
		return (er("minishel: syntax error near unexpected token `;'"));
	if (line[j] == '|')
		return (er("minishel: syntax error near unexpected token `|'"));
	if (line[j] == '&')
		return (er("minishel: syntax error near unexpected token `&'"));
	if (line[j] == '(')
		return (er("minishel: syntax error near unexpected token `('"));
	if (line[j] == ')')
		return (er("minishel: syntax error near unexpected token `)'"));
	if (line[j] == '>' && line[j - 1] == ' ')
		return (er("minishel: syntax error near unexpected token `>'"));
	if (line[j] == '*')
		return (er("minishel: wildcard '*' detected"));
	return (0);
}

static int	redir_check2(char *line, int j)
{
	if (line[j] == '<')
		return (er("minishel: syntax error near unexpected token `<'"));
	while (line[j] == ' ')
		j++;
	if (line[j] == '\0')
		return (er("minishel: syntax error near unexpected token `newline'"));
	if (line[j] == '&')
		return (er("minishel: syntax error near unexpected token `&'"));
	if (line[j] == ';')
		return (er("minishel: syntax error near unexpected token `;'"));
	if (line[j] == '|')
		return (er("minishel: syntax error near unexpected token `|'"));
	if (line[j] == '&')
		return (er("minishel: syntax error near unexpected token `&'"));
	if (line[j] == '(')
		return (er("minishel: syntax error near unexpected token `('"));
	if (line[j] == ')')
		return (er("minishel: syntax error near unexpected token `)'"));
	if ((line[j] == '>' && line[j - 1] == ' '))
		return (er("minishel: syntax error near unexpected token `>'"));
	if (line[j] == '*')
		return (er("minishel: wildcard '*' detected"));
	return (0);
}

static int	redir_check1(char *line, int j)
{
	if (line[j] == '>')
		return (er("minishel: syntax error near unexpected token `>'"));
	if (line[j] == '<')
		return (er("minishel: syntax error near unexpected token `<'"));
	while (line[j] == ' ')
		j++;
	if (line[j] == '\0')
		return (er("minishel: syntax error near unexpected token `newline'"));
	if (line[j] == '&')
		return (er("minishel: syntax error near unexpected token `&'"));
	if (line[j] == ';')
		return (er("minishel: syntax error near unexpected token `;'"));
	if (line[j] == '|')
		return (er("minishel: syntax error near unexpected token `|'"));
	if (line[j] == '&')
		return (er("minishel: syntax error near unexpected token `&'"));
	if (line[j] == '(')
		return (er("minishel: syntax error near unexpected token `('"));
	if (line[j] == ')')
		return (er("minishel: syntax error near unexpected token `)'"));
	if (line[j] == '>' && line[j - 1] == ' ')
		return (er("minishel: syntax error near unexpected token `>'"));
	if (line[j] == '*')
		return (er("minishel: wildcard '*' detected"));
	return (0);
}

int			r_c(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '>' && line[i + 1] == '>')
		{
			if (redir_check1(line, (i + 2)) == -1)
				return (-1);
		}
		else if (line[i] == '>')
		{
			if (redir_check2(line, (i + 1)) == -1)
				return (-1);
		}
		else if (line[i] == '<')
			if (redir_check3(line, (i + 1)) == -1)
				return (-1);
	}
	return (0);
}
