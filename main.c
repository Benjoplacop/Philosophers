/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:59:44 by bhennequ          #+#    #+#             */
/*   Updated: 2023/04/28 13:34:32 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	test_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf("Error: Only numeric params !\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	test_good_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Not negative arguments !\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_all(pthread_t *thread_philo, t_data *philo)
{
	free(thread_philo);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_data		*philo;
	pthread_t	*thread_philo;

	if (argc != 5 && argc != 6)
	{
		if (argc > 6)
			printf("Error: Too many arguments !\n");
		else
			printf("Error: To few arguments !\n");
		return (0);
	}
	if (!test_arg(argv) || !test_good_arg(argv))
		return (0);
	philo = malloc(sizeof(t_data));
	thread_philo = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	take_arg(argv, philo);
	create_thread(philo, thread_philo);
	free_all(thread_philo, philo);
	return (1);
}
