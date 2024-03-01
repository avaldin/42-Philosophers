/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:32:07 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/01 11:29:06 by avaldin          ###   ########.fr       */
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
# define SATISFIED 2

typedef struct	s_philo
{
	int				p_num;
	int 			eat_c;
	long 			last_eat;
	pthread_t		philo;
	bool			p_status;
	pthread_mutex_t *fork;
	struct s_philo	*next;
	struct s_data	*data;
}						t_philo;

typedef	struct s_data
{
	struct timeval	*time;
	int 			starter_c;
	long 			t_start;
	int 			c_philo;
	int 			c_end;
	int 			t_die;
	int 			t_sleep;
	int 			t_eat;
	int 			status;
	pthread_mutex_t init;
	struct s_philo	*p_first;
}						t_data;

int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);

void	pars_data(t_data *data, char **argv, int argc);
t_data	*init(char **argv, int argc);
void	clean_exit(t_data *data);
void	start(t_data *data);
long 	my_gettimeofday(struct timeval *tv, long t_start);
void	wait_all_thread(t_data *data);
long	take_forks(t_philo *philo, t_data *data);
bool	is_dead(t_philo *philo, t_data *data);
void 	*let_him_die(t_philo *philo, t_data *data);
long	give_back_forks(t_philo *philo, t_data *data);


#endif
