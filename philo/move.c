/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabbric <mfabbric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:07:19 by mfabbric          #+#    #+#             */
/*   Updated: 2023/12/11 12:43:38 by mfabbric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->philo_dead == 0)
	{
		printf("%lu %d %s\n", time, philo->id, str);
		philo->data->philo_dead = 1;
	}
	if (!philo->data->philo_dead)
		printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	messages(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->l_fork);
	messages(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	messages(SLEEPING, philo);
	ft_usleep(philo->data->timesleep);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = 1;
	philo->time_to_die = get_time();
	messages(EATING, philo);
	philo->number_of_meals++;
	ft_usleep(philo->data->timeeat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
