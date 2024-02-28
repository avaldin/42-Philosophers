/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:21 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/28 10:23:48 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	eat(t_philo *philo)
{
	if (!philo->p_num % 2)
		philo->last_eat = take_forks(philo->p_num, philo->next->fork, philo->fork, philo->data);
	else
		philo->last_eat = take_forks(philo->p_num, philo->fork, philo->next->fork, philo->data);
	if (philo->data->c_philo > 1)
	{
		printf("%ld %d is eating\n", philo->last_eat, philo->p_num + 1);
		usleep(1000 * philo->data->t_eat);
		if (pthread_mutex_unlock(philo->next->fork))
			clean_exit(philo->data);
		printf("philo %d give back is right fork\n", philo->p_num + 1);
		if (pthread_mutex_unlock(philo->fork))
			clean_exit(philo->data);
		printf("philo %d give back is left fork\n", philo->p_num + 1);

	}
	else if (pthread_mutex_unlock(philo->fork))
		clean_exit(philo->data);
}

bool	wait_to_eat(t_philo *philo, t_data *data)
{
	long	time;

	eat(philo);
	time = my_gettimeofday(data->time, data->t_start);
	printf("%ld philo %d , last eat var %ld, last eat calcul : %ld\n", time, philo->p_num, philo->last_eat, time - philo->last_eat);
	if (time - philo->last_eat >= data->t_die)
	{
		pthread_mutex_lock(&data->init);
		printf("%ld %d died because he didn't eat %ld\n", time, philo->p_num + 1, philo->last_eat);
		philo->p_status = DEAD;
		philo->data->status = DEAD;
		pthread_mutex_unlock(&data->init);
		return (0);
	}
	else if (philo->last_eat == philo->data->t_start)
		return (0);
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
	philo->p_status = ALIVE;
	if (pthread_mutex_unlock(data->p_first->fork))
		clean_exit(data);
	return (philo);
}

void	*life(void *arg)
{
	t_philo			*philo;
	t_data			*data;
	long			time;

	data = (t_data *)arg;
	philo = find_the_philo(data);
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);
	time = my_gettimeofday(data->time, data->t_start);
	printf("philo %d started at %ld\n",philo->p_num + 1, time);
	while (philo->p_status == ALIVE && data->status == ALIVE)
	{
		if (wait_to_eat(philo, data) == SUCCES)
		{
			my_gettimeofday(data->time, data->t_start);
			printf("%ld %d is sleeping %d time\n",
				  time,
				   philo->p_num + 1, 1000 * data->t_sleep);
			usleep(1000 * data->t_sleep);
			time = my_gettimeofday(data->time, data->t_start);
			printf("%ld %d is thinking\n",
				   time,
				   philo->p_num + 1);
		}
	}
	return (NULL);
}

void	start(t_data *data)
{
	int 			i;
	t_philo			*philo;

	philo = data->p_first;
	i = data->c_philo;
	data->starter_c = 0;
	pthread_mutex_lock(&data->init);
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
	usleep(10000);
	gettimeofday(data->time, NULL);
	data->t_start = data->time->tv_usec / 1000 + data->time->tv_sec * 1000;
	pthread_mutex_unlock(&data->init);
}