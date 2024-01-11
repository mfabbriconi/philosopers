/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabbric <mfabbric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:19:50 by mfabbric          #+#    #+#             */
/*   Updated: 2023/12/11 12:42:34 by mfabbric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->numphilo);
	if (!data->tid)
		return (error("ERROR WHILE ALLOCATING THREADS IDs", data));
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->numphilo);
	if (!data->fork_mutex)
		return (error("ERROR WHILE ALLOCATING FORKS", data));
	data->philo = malloc(sizeof(t_philo) * data->numphilo);
	if (!data->philo)
		return (error("ERROR WHILE ALLOCATING PHILOS", data));
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->numphilo)
		pthread_mutex_init(&data->fork_mutex[i], NULL);
	i = 0;
	data->philo[0].l_fork = &data->fork_mutex[0];
	data->philo[0].r_fork = &data->fork_mutex[data->numphilo - 1];
	i = 1;
	while (i < data->numphilo)
	{
		data->philo[i].l_fork = &data->fork_mutex[i];
		data->philo[i].r_fork = &data->fork_mutex[i - 1];
		i++;
	}
	return (0);
}

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->numphilo)
	{
		data->philo[i].id = i;
		data->philo[i].is_eating = 0;
		data->philo[i].number_of_meals = 0;
		data->philo[i].time_to_die = data->timedeath;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].lock, NULL);
	}
}

static int	init(t_data *data, int argc, char **argv)
{
	data->numphilo = (int) ft_atoi(argv[1]);
	data->timedeath = (u_int64_t) ft_atoi(argv[2]);
	data->timeeat = (u_int64_t) ft_atoi(argv[3]);
	data->timesleep = (u_int64_t) ft_atoi(argv[4]);
	if (argc == 6)
		data->musteat = ft_atoi(argv[5]);
	else
		data->musteat = -1;
	if (data->numphilo <= 0 || data->numphilo > 200 || data->timedeath <= 0
		|| data->timeeat <= 0 || data->timesleep <= 0)
		return (error("INVALID INPUT VALUES", NULL));
	if (mutex(data) == FAILURE)
		return (FAILURE);
	data->philo_dead = 0;
	data->finish = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 6 || argc < 5)
		return (1);
	if (check(argv))
		return (1);
	if (init(&data, argc, argv))
		return (1);
	if (alloc(&data))
		return (1);
	init_philo(&data);
	if (init_forks(&data))
		return (1);
	if (threadinit(&data))
		return (1);
	while (data.philo_dead != 1)
		;
	ft_exit(&data);
	return (0);
}
