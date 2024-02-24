/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:37:30 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/24 20:25:27 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"
#include <stdlib.h>

void	print_philo(t_philo *first)
{
	t_philo	*philo;

	philo = first;
	if (!philo)
		exit(5);
	printf("philo n%d, status = %d \n", philo->p_num, philo->status);
	if (!philo->next)
		exit(6);
	philo = philo->next;
	while (philo != first)
	{
		printf("philo n%d, status = %d \n", philo->p_num, philo->status);
		philo = philo->next;
	}
}

//void *loop(void *data)
//{
//	while (((t_data *)data)->status)
//	{
//		usleep(100000);
//	}
//	pthread_mutex_lock((pthread_mutex_t)fork[0]);
//	pthread_mutex_unlock(&((t_data *)data)->fork[0]);

//	return (args);
//}

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5)
		return (-1);
	data = NULL;
	data = init(argv);
	if (!data)
		clean_exit(data);
	print_philo(data->p_first);
	//if (pthread_create(&data->philo[0], 0, loop, &data))

	//while (status)
	//pthread_join(philo, NULL);
	//sleep(2);
//	while (*status)
//	{
//
//	}
//  msg die //// ou pas de while et que des join.
//
//
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