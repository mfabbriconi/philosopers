/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabbric <mfabbric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:31:44 by mfabbric          #+#    #+#             */
/*   Updated: 2023/12/11 12:44:43 by mfabbric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*path;

	if (nmemb > SIZE_MAX / size)
		return (NULL);
	if (nmemb == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	path = (void *)malloc(nmemb * size);
	if (!path)
		return (path);
	ft_bzero(path, nmemb * size);
	return (path);
}
