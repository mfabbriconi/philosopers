/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabbric <mfabbric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:59:58 by mfabbric          #+#    #+#             */
/*   Updated: 2023/12/01 15:38:22 by mfabbric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex(t_data *data)
{
	int	i;

	i = -1;
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->numphilo);
	if (!data->fork_mutex)
		return (FAILURE);
	while (++i < data->numphilo)
		pthread_mutex_init(&data->fork_mutex[i], NULL);
	pthread_mutex_init(&data->mutex, NULL);
	return (SUCCESS);
}

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	pthread_mutex_lock(&philo->data->write);
	//printf("data val: %llu", philo->data->philo_dead);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->philo_dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finish >= philo->data->numphilo)
			philo->data->philo_dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (philo->data->philo_dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() - philo->time_to_die >= philo->data->timedeath
			&& philo->is_eating == 0)
			messages(DIED, philo);
		if (philo->number_of_meals == philo->data->musteat)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finish++;
			philo->number_of_meals++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_point)
{
	t_philo	*philo;

	philo = (t_philo *) philo_point;
	philo->time_to_die = get_time();
	if (pthread_create(&philo->temp, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->philo_dead == 0)
	{
		eat(philo);
		messages(THINKING, philo);
	}
	if (pthread_join(philo->temp, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	threadinit(t_data *data)
{
	pthread_t	t0;
	int			i;

	i = -1;
	data->start_time = get_time();
	if (data->musteat > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philo[0]))
			return (error("ERROR WHILE CREATING THREADS", data));
	}
	while (++i < data->numphilo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]))
			return (error("ERROR WHILE CREATING THREADS", data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->numphilo)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error("ERROR WHILE JOINING THREADS", data));
	}
	return (0);
}
