/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:32:07 by avaldin           #+#    #+#             */
/*   Updated: 2024/02/25 14:29:19 by avaldin          ###   ########.fr       */
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
	int 			*last_eat;
	pthread_t		*philo;
	bool			p_status;
	bool			*f_status;
	pthread_mutex_t *fork;
	struct s_philo	*next;
	struct s_data	*data;
}						t_philo;

typedef	struct s_data
{
	struct timeval	*time;
	int 			t_start;
	int 			c_philo;
	int 			c_end;
	int 			t_die;
	int 			t_sleep;
	int 			t_eat;
	bool			status;
	struct s_philo	*p_first;
}						t_data;

t_data	*init(char **argv, int argc);
void	pars_data(t_data *data, char **argv, int argc);
int		ft_atoi(const char *nptr);
void	clean_exit(t_data *data);
void	start(t_data *data);

#endif
