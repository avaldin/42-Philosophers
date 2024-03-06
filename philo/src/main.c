/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:37:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/06 12:23:15 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	wait_the_end(t_data *data)
{
	t_philo	*philo;
	long	time;
	int		eating;

	philo = data->p_first;
	eating = data->c_philo;
	while (give_status(data) == ALIVE)
	{
		pthread_mutex_lock(&philo->m_eat);
		time = my_gettimeofday(data) - philo->last_eat;
		pthread_mutex_unlock(&philo->m_eat);
		eating -= eat_enought(philo, data, eating);
		time_to_die(philo, data, time);
		philo = philo->next;
	}
}

long	my_gettimeofday(t_data *data)
{
	long	time;
	int		secu;

	secu = gettimeofday(data->time, NULL);
	time = data->time->tv_usec / 1000
		+ data->time->tv_sec * 1000 - data->t_start;
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
		if (pthread_join(philo->philo, NULL))
			exit(1);
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
	clean_exit(data);
	return (0);
}
