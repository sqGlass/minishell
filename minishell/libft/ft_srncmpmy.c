/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srncmpmy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 16:26:40 by sglass            #+#    #+#             */
/*   Updated: 2021/03/07 15:24:04 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmpmy(const char *s1, const char *s2)
{
	unsigned int i;

	i = 0;
	while (((*(s1 + i) != 0) || (*(s2 + i) != 0)))
	{
		if (*((unsigned char *)s1 + i) > *((unsigned char *)s2 + i))
			return (1);
		if (*((unsigned char *)s1 + i) < *((unsigned char *)s2 + i))
			return (-1);
		i++;
	}
	return (0);
}
