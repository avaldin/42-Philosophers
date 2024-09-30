/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:32:07 by avaldin           #+#    #+#             */
/*   Updated: 2024/09/30 09:21:40 by avaldin          ###   ########.fr       */
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

typedef struct s_fork
{
	bool			taken;
	pthread_mutex_t mutex;
}				t_fork;

typedef struct s_philo
{
	int				p_num;
	int				eat_c;
	long			last_eat;
	int 			status;
	pthread_mutex_t	m_eat;
	pthread_t		philo;
	struct s_fork	fork[2];
	struct s_data	*data;
}						t_philo;

typedef struct s_data
{
	struct timeval	time;
	int				starter_c;
	long			t_start;
	int				c_philo;
	int				c_end;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				status;
	pthread_mutex_t	m_print;
	pthread_mutex_t	init;
	pthread_mutex_t	m_time;
	pthread_mutex_t	m_status;
	struct s_philo	philo[200];
	struct s_fork	fork[200];
}						t_data;

int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);

void	init_data(char **argv, int argc, t_data *data);
void	clean_exit(t_data *data);
void	start(t_data *data);
long	my_gettimeofday(t_data *data);
void	take_forks(int p_num, t_data *data);
bool	fork_try_take(t_fork *fork);
void	*let_him_die(t_philo *philo, t_data *data);
void	fork_give_back(t_data *data, int p_num);
void	wait_the_end(t_data *data);
int		get_status(t_data *data);
void	m_printf(char *str, int p_num, t_data *data);
int		eat_enought(t_philo *philo, t_data *data, int eating);
t_philo	*find_the_philo(t_data *data);
int		time_to_die(t_philo *philo, t_data *data, long time);

#endif
