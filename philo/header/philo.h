/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:32:07 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/24 18:44:07 by avaldin          ###   ########.fr       */
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

typedef struct	s_philo
{
	int				p_num;
	pthread_t		*philo;
	bool			status;
	pthread_mutex_t fork[2];
	struct s_philo	*next;
}						t_philo;

typedef	struct s_data
{
	struct timeval	*time;
	int 			p_count;
	int 			t_die;
	int 			t_sleep;
	int 			t_eat;
	struct s_philo	**p_first;
}						t_data;

t_data	*init(char **argv);
void	pars_data(t_data *data, char **argv);
int		ft_atoi(const char *nptr);


#endif
