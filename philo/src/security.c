/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:43 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/06 12:23:15 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	philosofree(t_data *data)
{
	t_philo	*next;
	t_philo	*philo;
	int		i;

	i = 0;
	philo = data->p_first;
	while (i < data->c_philo)
	{
		next = philo->next;
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->m_eat);
		free(philo);
		philo = next;
		i++;
	}
}

void	clean_exit(t_data *data)
{
	philosofree(data);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->init);
	pthread_mutex_destroy(&data->m_status);
	free(data->time);
	free(data);
	exit(2);
}

t_philo	*ft_lstnew(t_data *data, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	ft_bzero(philo, sizeof(t_philo));
	philo->p_num = i;
	philo->p_status = DEAD;
	pthread_mutex_init(&philo->m_eat, NULL);
	pthread_mutex_init(&philo->fork, NULL);
	philo->data = data;
	philo->next = NULL;
	return (philo);
}

void	init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 1;
	philo = ft_lstnew(data, 0);
	data->p_first = philo;
	while (i < data->c_philo)
	{
		philo->next = ft_lstnew(data, i);
		philo = philo->next;
		i++;
	}
	philo->next = data->p_first;
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
