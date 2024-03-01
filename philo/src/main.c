/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:37:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/01 16:46:19 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	wait_the_end(t_data *data)
{
	t_philo	*philo;
	long	time;

	philo = data->p_first;
	while (give_status(data) == ALIVE)
	{
		pthread_mutex_lock(&philo->m_eat);
		time = my_gettimeofday(data) - philo->last_eat;
		pthread_mutex_unlock(&philo->m_eat);
		eat_enought(data);
		if (time > data->t_die)
		{
			pthread_mutex_lock(&data->m_status);
			data->status = DEAD;
			printf("%ld %d died\n", time, philo->p_num + 1);
			pthread_mutex_unlock(&data->m_status);
		}
		usleep(500);
		philo = philo->next;
	}
}

long	my_gettimeofday(t_data *data)
{
	long	time;
	int 	secu;

	//pthread_mutex_lock(&data->m_time);
	secu = gettimeofday(data->time, NULL);
	time = data->time->tv_usec / 1000 + data->time->tv_sec * 1000 - data->t_start;
	//pthread_mutex_unlock(&data->m_time);
	if (!secu)
		return (time);
	return (-1);
}

void	thrend(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = data->c_philo;
	philo = data->p_first;
	while (i > 0)
	{
		pthread_join(philo->philo, NULL);
		i--;
		philo = philo->next;
	}
	i = data->c_philo;
	while (i > 0)
	{
		pthread_mutex_destroy(&philo->fork);
		i--;
		philo = philo->next;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (-1);
	data = NULL;
	data = init(argv, argc);
	if (!data)
		clean_exit(data);
	start(data);
	thrend(data);
	return (0);
}
