/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:21 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/26 10:50:59 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long	eat(t_philo *philo, bool *fork_left, bool *fork_right, long last_eat)
{
	long eating_time;

	if (pthread_mutex_lock(philo->fork))
		clean_exit(philo->data);
	*fork_left = 0;
	my_gettimeofday(philo->data->time);
	eating_time = philo->data->time->tv_usec - philo->data->t_start;
	//printf("eating time = %ld, tim = %ld, start= %ld\n", eating_time, philo->data->time->tv_usec, philo->data->t_start);
	printf("%ld %d has taken a fork\n", eating_time, philo->p_num + 1);
	if (pthread_mutex_lock(philo->next->fork))
		clean_exit(philo->data);
	*fork_right = 0;
	printf("%ld %d has taken a fork\n", eating_time, philo->p_num + 1);
	last_eat = eating_time;
	printf("%ld %d is eating, time eating : %d\n", eating_time, philo->p_num + 1, 1000 * philo->data->t_eat);
	usleep(1000 * philo->data->t_eat);
	if (pthread_mutex_unlock(philo->next->fork))
		clean_exit(philo->data);
	*fork_right = 1;
	if (pthread_mutex_unlock(philo->fork))
		clean_exit(philo->data);
	*fork_left = 1;
	return (last_eat);
}

bool	wait_to_eat(t_philo *philo, int t_die, struct timeval *time)
{
	bool	*fork_left;
	bool	*fork_right;

	fork_left = &philo->f_status;
	fork_right = &philo->next->f_status;
	while (!*fork_left || !*fork_right)
	{
		my_gettimeofday(time);
		if (time->tv_usec - philo->last_eat >= t_die)
		{
			printf("%ld %d died\n", (time->tv_usec - philo->data->t_start), philo->p_num + 1);
			philo->p_status = DEAD;
			return (0);
		}
	}
	philo->last_eat = eat(philo, fork_left, fork_right, philo->last_eat);
	my_gettimeofday(time);
	if (my_gettimeofday(time) - philo->last_eat >= t_die)
	{
		printf("%ld %d died\n", time->tv_usec - philo->data->t_start, philo->p_num + 1);
		philo->p_status = DEAD;
		return (0);
	}
	return (1);
}

t_philo	*find_the_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->p_first;
	if (pthread_mutex_lock(data->p_first->fork))
		clean_exit(data);
	i = data->starter_c;
	while (i > 0)
	{
		philo = philo->next;
		i--;
	}
	data->starter_c++;
	if (pthread_mutex_unlock(data->p_first->fork))
		clean_exit(data);
	return (philo);

}

void	*life(void *arg)
{
	t_philo			*philo;
	t_data			*data;
	struct timeval	*time;

	data = (t_data *)arg;
	philo = find_the_philo(data);
	time = data->time;
	philo->last_eat = data->t_start;
	printf("philo %d start\n", philo->p_num + 1);
	while (philo->p_status == ALIVE || data->status == ALIVE)
	{
		if (wait_to_eat(philo, data->t_die,data->time) == SUCCES)
		{
			my_gettimeofday(data->time);
			printf("%ld %d is sleeping\n",
				   time->tv_usec - data->t_start,
				   philo->p_num + 1);
			usleep(1000 * data->t_sleep);
			my_gettimeofday(data->time);
			printf("%ld %d is thinking\n",
				   (time->tv_usec - data->t_start),
				   philo->p_num + 1);
		}
	}
	return (NULL);
}

void	start(t_data *data)
{
	int 	i;
	t_philo	*philo;

	philo = data->p_first;
	i = data->c_philo;
	data->starter_c = 0;
	my_gettimeofday(data->time);
	data->t_start = data->time->tv_usec;
	printf("time start = %ld\n", data->t_start);
	my_gettimeofday(data->time);
	printf("det time %ld, diff %ld\n", data->time->tv_usec, data->time->tv_usec - data->t_start);
	while (i > 0)
	{
		if (pthread_create(&philo->philo, NULL, life, data))
		{
			printf("pthread_create failed\n");
			clean_exit(data);
		}
		philo = philo->next;
		i--;
	}
}