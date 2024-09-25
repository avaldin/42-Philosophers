/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:43 by avaldin           #+#    #+#             */
/*   Updated: 2024/09/25 11:59:13 by avaldin          ###   ########.fr       */
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

void	init_data(char **argv, int argc, t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->c_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->c_end = ft_atoi(argv[5]);
	if (data->c_philo < 1 || data->t_die < 1
		|| data->t_eat < 0 || data->t_sleep < 0 || (argc == 6
		&& data->c_end < 1))
	{
		printf("bad arguments\n");
		exit(3);
	}
	init_philo(data);
	if (!data->p_first)
		clean_exit(data);
	data->status = ALIVE;
}
