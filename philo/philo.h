/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabbric <mfabbric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:16:52 by mfabbric          #+#    #+#             */
/*   Updated: 2023/12/01 16:29:55 by mfabbric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

//	error_int
# define TRUE 		1
# define SUCCESS	1
# define FALSE		0
# define ERROR		0
# define FAILURE	0

//	philo_messages
# define TAKE_FORKS "has taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define DIED "died"

struct	s_data;

typedef struct s_philo
{
	pthread_t			temp;
	int					id;
	int					is_eating;
	int					number_of_meals;
	u_int64_t			time_to_die;
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		lock;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int					numphilo;
	u_int64_t			timedeath;
	u_int64_t			timeeat;
	u_int64_t			timesleep;
	int					musteat;
	int					finish;
	u_int64_t			start_time;
	u_int64_t			philo_dead;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		mutex;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
	pthread_t			*tid;
	t_philo				*philo;
}	t_data;

long long	ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *s, int c, size_t len);
int			ft_strcmp(char *s1, char *s2);
void		ft_close(void);
int			error(char *str, t_data *data);
void		*routine(void *philo_point);
u_int64_t	get_time(void);

int			check(char **argv);
int			threadinit(t_data *data);
int			mutex(t_data *data);
int			ft_usleep(useconds_t time);
void		messages(char *str, t_philo *philo);
void		eat(t_philo *philo);
void		ft_exit(t_data *data);

#endif
