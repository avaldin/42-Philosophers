/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:43 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/24 20:40:17 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	philosofree(t_philo *philo)
{
	t_philo	*next;

	while (philo)
	{
		next = NULL;
		if (philo->next)
			next = philo->next;
		free(philo);
		philo = next;
	}
}

void	clean_exit(t_data *data)
{

	philosofree(data->p_first);
	//fork_free;
	free(data);
	perror(errno);
	exit(2);
}

void	init_philo(t_data *data)
{
	t_philo	*philo;
	t_philo	*p_prev;
	int 	i;

	i = 0;
	data->p_first = NULL;
	while (i < data->p_count)
	{
		philo = NULL;
		philo = malloc(sizeof(t_philo));
		if (!philo)
			clean_exit(data);
		philo->p_num = i;
		philo->status = ALIVE;
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

t_data	*init(char **argv)
{
	t_data		*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("data malloc failed\n");
		exit(EXIT_FAILURE);
	}
	pars_data(data, argv);
	init_philo(data);
	if (!data->p_first)
		clean_exit(data);
//	data->fork = malloc(sizeof(pthread_mutex_t) * data->p_count);
	return (data);
}