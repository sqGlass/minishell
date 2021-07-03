/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:24:02 by mlorette          #+#    #+#             */
/*   Updated: 2021/02/20 14:54:07 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;

	i = 0;
	while (((*(s1 + i) != 0) || (*(s2 + i) != 0)) && i < n)
	{
		if (*((unsigned char *)s1 + i) > *((unsigned char *)s2 + i))
			return (1);
		if (*((unsigned char *)s1 + i) < *((unsigned char *)s2 + i))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_strncmpeq(const char *s1, const char *s2, size_t n)
{
	unsigned int i;

	i = 0;
	while (((*(s1 + i) != 0) || (*(s2 + i) != 0)) && i < n)
	{
		if (*((unsigned char *)s1 + i) > *((unsigned char *)s2 + i))
			return (1);
		if (*((unsigned char *)s1 + i) < *((unsigned char *)s2 + i))
			return (-1);
		i++;
	}
	if (s1[i] != '=')
		return (1);
	return (0);
}
