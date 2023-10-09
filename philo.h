/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:26:10 by mreidenb          #+#    #+#             */
/*   Updated: 2023/08/23 00:40:54 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

# define BOLD    "\033[1m"
# define UNDERLINE "\033[4m"
# define REVERSE  "\033[7m"

typedef struct s_rules
{
	long			amount;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	long			times_to_eat;
	pthread_mutex_t	death;
	bool			dead;
	pthread_mutex_t	printing;
}			t_rules;

typedef struct s_philo
{
	int				n;
	time_t			last_ate;
	long			to_eat;
	t_rules			*rules;
	pthread_t		id;
	pthread_mutex_t	right;
	pthread_mutex_t	*left;
	pthread_mutex_t	eating;
	pthread_mutex_t	tte;
}	t_philo;

//philo

t_philo		**bear_philos(t_rules *rules);
void		sit_philos_down(t_philo **philos);
int			let_philos_free(t_philo **philos, t_rules *rules);

//habits

void		eating(t_philo *philo);
void		thinking(t_philo *philo);
void		sleeping(t_philo *philo);

//time

long		current_time_ms(void);
void		p_sleep(time_t ms);

//utlis

void		print_process(t_philo *philo, char *msg, char *format);
long		ft_atoi_l(const char *str);
int			ft_isdigit(int c);
int			par_sz(int argc, char *argv[]);
int			is_num(int argc, char *argv[]);

#endif
