/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:32:07 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/23 12:10:23 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define DEAD 0
# define ALIVE 1
# define FAIL 0
# define SUCCES 1

typedef	struct s_data
{
	struct timeval	*time;
	bool			status;
	pthread_t		*philo;
	pthread_mutex_t *fork;
	int 			p_count;

}						t_data;

t_data	*init(char **argv);
void	pars_data(t_data *data, char **argv);

#endif
