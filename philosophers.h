/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:09:25 by bhennequ          #+#    #+#             */
/*   Updated: 2023/04/28 14:43:56 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define PINK "\033[0;45m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

typedef struct s_philosopher
{
	int				nb_philo;
	int				id;
	int				fork_a;
	int				fork_b;
	int				count_eat;
	int				eat_ok;
	pthread_mutex_t	mutex_last_eat;
	pthread_mutex_t	mutex_eat;
	long long		last_eat;
	struct s_data	*data;
}				t_philosopher;

typedef struct s_data
{
	int				nb_philo;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				eat_nb;
	int				end;
	long long		start_time;
	pthread_mutex_t	mutex_end;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*forks;
	int				*is_lock;
}				t_data;

int			mutex_end(t_philosopher *philo);
int			mutex_eat_ok(t_philosopher *philo);
long long	mutex_last_eat(t_philosopher *philo);
int			ft_isdigit(int c);
long long	ft_atoi(const char *str);
void		print_mess(t_philosopher *philo, char *str, int unlock);
void		leave_mutex_if_dead(t_philosopher *philo, int left_fork,
				int right_fork);
char		*color_philo(t_philosopher *philo);
void		lock_mutex(t_philosopher *philo);
void		unlock_mutex(t_philosopher *philo);
int			philo_die(t_philosopher philo);
void		init_philo(t_data *philo, t_philosopher *philosophers, int i);
void		take_arg(char **argv, t_data *philo);
long long	get_time(void);
void		create_thread(t_data *data, pthread_t *thread_philo);
void		*philosopher(t_philosopher *philo);
void		eat_sleep(t_philosopher *philo);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
