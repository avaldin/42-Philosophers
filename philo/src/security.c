/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:43 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/01 15:59:51 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	philosofree(t_philo *philo, int p_count)
{
	t_philo	*next;
	int		i;

	i = 0;
	while (i < p_count)
	{
		next = philo->next;
		pthread_mutex_destroy(&philo->fork);
		free(philo);
		philo = next;
		i++;
	}
}

void	clean_exit(t_data *data)
{
	printf("exit\n");
	philosofree(data->p_first, data->c_philo);
	free(data);
	exit(2);
}

void	init_philo_utils(t_philo *philo, int i, t_data *data)
{
	philo->p_num = i;
	philo->p_status = DEAD;
	pthread_mutex_init(&philo->m_eat, NULL);
	pthread_mutex_init(&philo->fork, NULL);
	philo->data = data;
}

void	init_philo(t_data *data)
{
	t_philo	*philo;
	t_philo	*p_prev;
	int		i;

	i = 0;
	while (i < data->c_philo)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			clean_exit(data);
		ft_bzero(philo, sizeof(t_philo));
		init_philo_utils(philo, i, data);
		if (i)
			p_prev->next = philo;
		else
			data->p_first = philo;
		p_prev = philo;
		philo = philo->next;
		i++;
	}
	p_prev->next = data->p_first;
}

t_data	*init(char **argv, int argc)
{
	t_data		*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("data malloc failed\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(data, sizeof(t_data));
	data->time = malloc(sizeof(struct timeval));
	pars_data(data, argv, argc);
	init_philo(data);
	if (!data->p_first)
		clean_exit(data);
	data->status = ALIVE;
	return (data);
}
