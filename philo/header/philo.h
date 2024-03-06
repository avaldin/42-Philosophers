/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <avaldin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:32:07 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/06 08:57:18 by avaldin          ###   ########.fr       */
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

typedef struct s_philo
{
	int				p_num;
	int				eat_c;
	long			last_eat;
	pthread_mutex_t	m_eat;
	pthread_t		philo;
	bool			p_status;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_data	*data;
}						t_philo;

typedef struct s_data
{
	struct timeval	*time;
	int				starter_c;
	long			t_start;
	int				c_philo;
	int				c_end;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				status;
	pthread_mutex_t m_print;
	pthread_mutex_t	init;
	pthread_mutex_t	m_status;
	struct s_philo	*p_first;
}						t_data;

int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);

void	pars_data(t_data *data, char **argv, int argc);
t_data	*init(char **argv, int argc);
void	clean_exit(t_data *data);
void	start(t_data *data);
long	my_gettimeofday(t_data *data);
void	take_forks(t_philo *philo, t_data *data);
void	*let_him_die(t_philo *philo, t_data *data);
long	give_back_forks(t_philo *philo, t_data *data);
void	wait_the_end(t_data *data);
int		give_status(t_data *data);
int		eat_enought(t_philo *philo, t_data *data, int eating);
t_philo	*find_the_philo(t_data *data);
int 	time_to_die(t_philo *philo, t_data *data, long time);


#endif
