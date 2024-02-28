/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:36:39 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/28 16:22:16 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/philo.h"

int	eat_enought(t_data *data)
{

}

long	take_forks(t_philo *philo, t_data *data)
{
	if (philo->p_num % 2 == 0)
	{
		if (pthread_mutex_lock(philo->next->fork))
			clean_exit(data);
		printf("%ld %d has taken a fork\n", my_gettimeofday(data->time, data->t_start), philo->p_num + 1);
		if (pthread_mutex_lock(philo->fork))
			clean_exit(data);
		printf("%ld %d has taken a fork\n", my_gettimeofday(data->time, data->t_start), philo->p_num + 1);
	}
	else
	{
		if (pthread_mutex_lock(philo->fork))
			clean_exit(data);
		printf("%ld %d has taken a fork\n", my_gettimeofday(data->time, data->t_start), philo->p_num + 1);
		if (pthread_mutex_lock(philo->next->fork))
			clean_exit(data);
		printf("%ld %d has taken a fork\n", my_gettimeofday(data->time, data->t_start), philo->p_num + 1);
	}
	if (is_dead(philo, data))
	{
		give_back_forks(philo, data);
		return (-1);
	}
	return (0);
}

bool	is_dead(t_philo *philo, t_data *data)
{
	long	time;

	time = my_gettimeofday(data->time, data->t_start);
	pthread_mutex_lock(&data->init);
	if (time - philo->last_eat > data->t_die)
	{
		printf("%ld %d died\n", time, philo->p_num + 1);
		data->status = DEAD;
		pthread_mutex_unlock(&data->init);
		return (1);
	}
	else if (data->status == DEAD)
	{
		pthread_mutex_unlock(&data->init);
		return (1);
	}
	pthread_mutex_unlock(&data->init);
	return (0);
}

void *let_him_die(t_philo *philo, t_data *data)
{
	if (pthread_mutex_lock(philo->fork))
		clean_exit(philo->data);
	printf("%ld %d has taken a fork\n",
		   my_gettimeofday(data->time, data->t_start), philo->p_num + 1);
	while (is_dead(philo, data) == 0)
		usleep(5000);
	if (pthread_mutex_unlock(philo->fork))
		clean_exit(philo->data);
	return (0);
}

long	give_back_forks(t_philo *philo, t_data *data)
{
	if (!philo->p_num % 2)
	{
		if (pthread_mutex_unlock(philo->next->fork))
			clean_exit(data);
		if (pthread_mutex_unlock(philo->fork))
			clean_exit(data);
	}
	else
	{
		if (pthread_mutex_unlock(philo->fork))
			clean_exit(data);
		if (pthread_mutex_unlock(philo->next->fork))
			clean_exit(data);
	}
	return (0);
}