/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:43 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/24 18:44:07 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	clean_exit(t_data *data)
{
	//int i;

	//i = 0;
	if (data && data->philo)
	{
//		while (data->philo[i] && i < data->p_count)
//		{
//			if (pthread_join(data->philo[i], NULL))
//				perror("pthread_join failed");
//			i++;
//		}
		free(data->philo);
	}
	free(data);
	exit(2);
}

t_philo	**init_philo(t_data *data)
{
	t_philo	**p_first;
	t_philo	*philo;
	t_philo	*p_prev;
	int 	i;

	i = 0;
	p_first = &philo;
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
		p_prev = philo;
		philo = philo->next;
		i++;
	}
	p_prev->next = *p_first;
	return (p_first);
}

t_data	*init(char **argv)
{
	t_data		*data;
	t_philo		*philo;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		clean_exit(data);
	pars_data(data, argv);
	data->p_first = init_philo(data);
	if (!data->p_first)
		clean_exit(data);
//	data->fork = malloc(sizeof(pthread_mutex_t) * data->p_count);
	return (data);
}