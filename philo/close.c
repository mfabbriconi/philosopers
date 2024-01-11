/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabbric <mfabbric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:32:03 by mfabbric          #+#    #+#             */
/*   Updated: 2023/11/27 16:06:52 by mfabbric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_data(t_data	*data)
{
	if (data->tid)
		free(data->tid);
	if (data->fork_mutex)
		free(data->fork_mutex);
	if (data->philo)
		free(data->philo);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->numphilo)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
		pthread_mutex_destroy(&data->philo[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}

int	error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}
