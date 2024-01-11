/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabbric <mfabbric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:32:35 by mfabbric          #+#    #+#             */
/*   Updated: 2023/10/23 11:43:33 by mfabbric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned int	i;
	char			*dest;

	dest = s;
	i = 0;
	while (i < len)
	{
		dest[i] = c;
		i++;
	}
	return ((void *)s);
}
