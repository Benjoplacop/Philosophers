/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:17:32 by bhennequ          #+#    #+#             */
/*   Updated: 2023/04/27 18:49:05 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_mess(t_philosopher *philo, char *str, int unlock)
{
	(void)unlock;
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!mutex_end(philo) && !mutex_eat_ok(philo))
		printf("%s%lli ms - %i %s%s\n", color_philo(philo),
			get_time() - philo->data->start_time, philo->id + 1, str, RESET);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void	*philo_test(t_philosopher *philo)
{
	long long	time_left;

	while (1)
	{
		time_left = get_time() - mutex_last_eat(philo);
		if (mutex_end(philo) || mutex_eat_ok(philo))
			break ;
		else if (time_left >= philo->data->time2die)
		{
			print_mess(philo, DEAD, 0);
			pthread_mutex_lock(&philo->data->mutex_end);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->mutex_end);
			break ;
		}
		usleep(100);
	}
	return (0);
}

static	void	routine(t_philosopher *philo)
{
	pthread_t	thread_test;

	pthread_create(&thread_test, NULL, (void *)philo_test, philo);
	while (1)
	{
		if (mutex_end(philo) || mutex_eat_ok(philo))
			break ;
		if (philo->id % 2 == 1)
			usleep(5000);
		lock_mutex(philo);
		unlock_mutex(philo);
		print_mess(philo, SLEEP, 1);
		usleep(philo->data->time2sleep * 1000);
	}
	pthread_join(thread_test, NULL);
	return ;
}

void	*philosopher(t_philosopher *philo)
{
	if (philo->data->nb_philo == 1)
	{
		print_mess(philo, FORK, 1);
		usleep(philo->data->time2die * 1000);
		print_mess(philo, DEAD, 0);
		return (0);
	}
	routine(philo);
	return (0);
}
