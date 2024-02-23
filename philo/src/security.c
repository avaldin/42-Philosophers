/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:51:43 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/23 12:11:43 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	clean_exit(t_data *data)
{
	int i;

	i = 0;
	while (i < )
}

t_data	*init(char **argv)
{
	pthread_t	*philo;
	t_data		*data;

	philo = NULL;
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		clean_exit(data);
	pars_data(data, argv);
	philo = malloc(sizeof(pthread_t) * data->p_count);
	if (!philo)
		clean_exit(data);
}