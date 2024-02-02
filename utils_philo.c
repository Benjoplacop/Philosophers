/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:41:21 by bhennequ          #+#    #+#             */
/*   Updated: 2023/04/28 14:45:18 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*color_philo(t_philosopher *philo)
{
	if (philo->id % 8 == 0)
		return (PINK);
	else if (philo->id % 8 == 1)
		return (RED);
	else if (philo->id % 8 == 2)
		return (GREEN);
	else if (philo->id % 8 == 3)
		return (YELLOW);
	else if (philo->id % 8 == 4)
		return (BLUE);
	else if (philo->id % 8 == 5)
		return (MAGENTA);
	else if (philo->id % 8 == 6)
		return (CYAN);
	else
		return (WHITE);
}

void	init_philo(t_data *philo, t_philosopher *philosophers, int i)
{
	philosophers[i].id = i;
	philosophers[i].count_eat = 0;
	philosophers[i].eat_ok = 0;
	philosophers[i].last_eat = get_time();
	philosophers[i].nb_philo = philo->nb_philo;
	philosophers[i].data = philo;
	if (philosophers[i].id % 2 == 0)
	{
		philosophers[i].fork_a = i;
		philosophers[i].fork_b = (i + 1) % philo->nb_philo;
	}
	else
	{
		philosophers[i].fork_a = (i + 1) % philo->nb_philo;
		philosophers[i].fork_b = i;
	}
	pthread_mutex_init(&philosophers[i].mutex_eat, NULL);
	pthread_mutex_init(&philosophers[i].mutex_last_eat, NULL);
}

void	lock_mutex(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork_a]);
	pthread_mutex_lock(&philo->data->forks[philo->fork_b]);
	print_mess(philo, FORK, 1);
	print_mess(philo, FORK, 1);
}

void	unlock_mutex(t_philosopher *philo)
{
	print_mess(philo, EAT, 1);
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex_last_eat);
	philo->count_eat = philo->count_eat + 1;
	if (philo->count_eat == philo->data->eat_nb)
	{	
		pthread_mutex_lock(&philo->mutex_eat);
		philo->eat_ok = 1;
		pthread_mutex_unlock(&philo->mutex_eat);
	}
	usleep(philo->data->time2eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_a]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_b]);
}
