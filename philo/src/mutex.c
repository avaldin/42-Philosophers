/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:27:17 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/01 15:49:58 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	give_status(t_data *data)
{
	int status;

	pthread_mutex_lock(&data->m_status);
	status = data->status;
	pthread_mutex_unlock(&data->m_status);
	return (status);
}
