/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:36:39 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/28 09:57:24 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/philo.h"

long	take_forks(int p_num, pthread_mutex_t *first_f, pthread_mutex_t *second_f, t_data *data)
{
	long time;

	if (data->c_philo > 1)
	{
		if (pthread_mutex_lock(first_f))
			clean_exit(data);
		time  = my_gettimeofday(data->time, data->t_start);
		printf("%ld %d has taken a fork\n", time, p_num + 1);
		if (pthread_mutex_lock(second_f))
			clean_exit(data);
		time = my_gettimeofday(data->time, data->t_start);
		printf("%ld %d has taken a fork\n", time, p_num + 1);
		return (time);
	}
	if (pthread_mutex_lock(second_f))
		clean_exit(data);
	time = my_gettimeofday(data->time, data->t_start);
	printf("%ld %d has taken a fork\n", time, p_num + 1);
	return (data->t_start);
}