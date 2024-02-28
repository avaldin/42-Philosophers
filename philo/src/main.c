/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:37:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/28 10:16:36 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long my_gettimeofday(struct timeval *tv, long t_start)
{
	if (!gettimeofday(tv, NULL))
		return (tv->tv_usec / 1000 + tv->tv_sec * 1000 - t_start);
	return (-1);
}

void	thrend(t_data *data)
{
	t_philo	*philo;
	int 	i;

	i = data->c_philo;
	philo = data->p_first;
	while (i > 0)
	{
		pthread_join(philo->philo, NULL);
		i++;
		philo = philo->next;
	}
	i = data->c_philo;
	while (i > 0)
	{
		pthread_mutex_destroy(philo->fork);
		i++;
		philo = philo->next;
	}
}

int main(int argc, char **argv)
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















//
//void *vie(void *status)
//{
//	usleep(10000000);
//	*(bool *)status = DEAD;
//	return (NULL);
//}
//
//int main(void)
//{
//	bool		*status;
//	pthread_t	p_vie;
//
//	status = malloc(sizeof(bool));
//	if (!status)
//		return (1);
//	*status = ALIVE;
//	if (pthread_create(&p_vie, NULL, vie, status))
//		return (1);
//	printf("la vie va bien\n");
//	pthread_join(p_vie, NULL);
//	printf("MORT\n");
//	free(status);
//	return (0);
//}