/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:44:19 by bhennequ          #+#    #+#             */
/*   Updated: 2023/04/28 14:45:38 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_arg(char **argv, t_data *philo)
{
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time2die = ft_atoi(argv[2]);
	philo->time2eat = ft_atoi(argv[3]);
	philo->time2sleep = ft_atoi(argv[4]);
	philo->start_time = get_time();
	philo->end = 0;
	if (argv[5])
		philo->eat_nb = ft_atoi(argv[5]);
	else
		philo->eat_nb = -1;
}

long long	get_time(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

static void	free_thread(t_philosopher *philosophers, t_data *philo,
		pthread_t *thread_philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
		pthread_join(thread_philo[i], NULL);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_mutex_destroy(&philo->forks[i]);
	pthread_mutex_destroy(&philo->mutex_print);
	pthread_mutex_destroy(&philo->mutex_end);
	if (philo->nb_philo != 1)
	{
		pthread_mutex_destroy(&philosophers->mutex_last_eat);
		pthread_mutex_destroy(&philosophers->mutex_eat);
	}
	free(philosophers);
	free(philo->forks);
}

void	create_thread(t_data *data, pthread_t *thread_philo)
{
	int				i;
	t_philosopher	*philosophers;

	philosophers = malloc(sizeof(t_philosopher) * (data->nb_philo + 1));
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->nb_philo));
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_end, NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		init_philo(data, philosophers, i);
		pthread_create(&thread_philo[i], NULL,
			(void *) philosopher, &philosophers[i]);
	}
	free_thread(philosophers, data, thread_philo);
}
