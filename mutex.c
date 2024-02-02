/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:43:53 by bhennequ          #+#    #+#             */
/*   Updated: 2023/04/27 18:48:08 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mutex_end(t_philosopher *philo)
{
	int	n;

	pthread_mutex_lock(&philo->data->mutex_end);
	n = philo->data->end;
	pthread_mutex_unlock(&philo->data->mutex_end);
	return (n);
}

int	mutex_eat_ok(t_philosopher *philo)
{
	int	n;

	pthread_mutex_lock(&philo->mutex_eat);
	n = philo->eat_ok;
	pthread_mutex_unlock(&philo->mutex_eat);
	return (n);
}

long long	mutex_last_eat(t_philosopher *philo)
{
	long long	n;

	pthread_mutex_lock(&philo->mutex_last_eat);
	n = philo->last_eat;
	pthread_mutex_unlock(&philo->mutex_last_eat);
	return (n);
}
