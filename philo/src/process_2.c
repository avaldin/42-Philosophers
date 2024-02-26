/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:36:39 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/26 16:30:31 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/philo.h"

long	take_forks(int p_num, pthread_mutex_t *first_f, pthread_mutex_t *second_f, t_data *data)
{
	long fork_time;

	if (data->c_philo > 1)
	{
		if (pthread_mutex_lock(first_f))
			clean_exit(data);
		my_gettimeofday(data->time);
		fork_time = data->time->tv_usec - data->t_start;
		printf("%ld %d has taken a fork\n", fork_time, p_num + 1);
		if (pthread_mutex_lock(second_f))
			clean_exit(data);
		my_gettimeofday(data->time);
		fork_time = data->time->tv_usec - data->t_start;
		printf("%ld %d has taken a fork\n", fork_time, p_num + 1);
		return (fork_time);
	}
	if (pthread_mutex_lock(second_f))
		clean_exit(data);
	my_gettimeofday(data->time);
	fork_time = data->time->tv_usec - data->t_start;
	printf("%ld %d has taken a fork\n", fork_time, p_num + 1);
	return (data->t_start);
}