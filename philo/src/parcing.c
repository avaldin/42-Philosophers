/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:52:29 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/23 12:24:39 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	pars_data(t_data *data, char **argv)
{
	data->p_count = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_die = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
}