/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:21 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/25 14:29:19 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	eat(t_philo *philo, bool *fork_left, bool *fork_right, int *last_eat)
{
	if (pthread_mutex_lock(philo->fork))
		clean_exit(philo->data);
	*fork_left = 0;
	printf("%d %d has taken a fork\n", (gettimeofday(philo->data->time, NULL) - philo->data->t_start), philo->p_num + 1);
	if (pthread_mutex_lock(philo->next->fork))
		clean_exit(philo->data);
	*fork_right = 0;
	printf("%d %d has taken a fork\n", (gettimeofday(philo->data->time, NULL) - philo->data->t_start), philo->p_num + 1);
	*last_eat = gettimeofday(philo->data->time, NULL) - philo->data->t_start;
	printf("%d %d is eating\n", *last_eat, philo->p_num + 1);
	usleep(1000 * philo->data->t_eat);
	if (pthread_mutex_unlock(philo->next->fork))
		clean_exit(philo->data);
	*fork_right = 1;
	if (pthread_mutex_unlock(philo->fork))
		clean_exit(philo->data);
	*fork_left = 1;
}

bool	wait_to_eat(t_philo *philo, int t_die, struct timeval *time)
{
	bool	*fork_left;
	bool	*fork_right;

	fork_left = philo->f_status;
	fork_right = philo->next->f_status;
	while (*fork_left && *fork_right)
	{
		if (gettimeofday(time, NULL) - *philo->last_eat >= t_die)
		{
			printf("%d %d died\n", (gettimeofday(time, NULL) - philo->data->t_start), philo->p_num + 1);
			philo->p_status = DEAD;
			return (0);
		}
	}
	eat(philo, fork_left, fork_right, philo->last_eat);
	if (gettimeofday(time, NULL) - *philo->last_eat >= t_die)
	{
		printf("%d %d died\n", (gettimeofday(time, NULL) - philo->data->t_start), philo->p_num + 1);
		philo->p_status = DEAD;
		return (0);
	}
	return (1);
}

void	*life(void *arg)
{
	t_philo	*philo;
	t_data	*data;


	philo = (t_philo *)arg;
	data = philo->data;
	*philo->last_eat = data->t_start;
	while (philo->p_status == ALIVE || data->status == ALIVE)
	{
		if (wait_to_eat(philo, data->t_die,data->time) == SUCCES)
		{
			printf("%d %d is sleeping\n",
				   (gettimeofday(data->time, NULL) - data->t_start),
				   philo->p_num + 1);
			usleep(1000 * data->t_sleep);
			printf("%d %d is thinking\n",
				   (gettimeofday(data->time, NULL) - data->t_start),
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
	data->t_start = gettimeofday(data->time, NULL);
	while (i > 0)
	{
		if (pthread_create(philo->philo, NULL, life, data))
		{
			printf("pthread_create failed\n");
			clean_exit(data);
		}
		i++;
	}
}