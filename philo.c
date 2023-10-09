/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:54:42 by mreidenb          #+#    #+#             */
/*   Updated: 2023/10/09 13:08:43 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	bad_input(void)
{
	printf("Wrong Input Format\n");
	printf("Please Format input Like Following: \n");
	printf("./philo <number of philosophers(pos int)> <time_to_die(ms)> ");
	printf("<time_to_eat(ms)> <time_to_sleep(ms)> ");
	printf("[number_of_times_each_philosopher_must_eat(pos int)] \n");
	return (-1);
}

t_rules	*init_rules(int argc, char *argv[])
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	rules->start_time = current_time_ms();
	rules->amount = ft_atoi_l(argv[1]);
	rules->time_to_die = ft_atoi_l(argv[2]);
	rules->time_to_eat = ft_atoi_l(argv[3]);
	rules->time_to_sleep = ft_atoi_l(argv[4]);
	pthread_mutex_init(&rules->death, NULL);
	rules->dead = false;
	pthread_mutex_init(&rules->printing, NULL);
	rules->times_to_eat = INT_MAX;
	if (argc == 6)
		rules->times_to_eat = ft_atoi_l(argv[5]);
	return (rules);
}

int	starvation(t_philo *philo)
{
	pthread_mutex_lock(&philo->eating);
	if (philo->last_ate + philo->rules->time_to_die < current_time_ms())
	{
		pthread_mutex_unlock(&philo->eating);
		pthread_mutex_lock(&philo->rules->death);
		philo->rules->dead = true;
		pthread_mutex_unlock(&philo->rules->death);
		return (1);
	}
	else
		return (pthread_mutex_unlock(&philo->eating));
}

void	*finish(t_rules *rules)
{
	pthread_mutex_lock(&rules->death);
	rules->dead = true;
	pthread_mutex_unlock(&rules->death);
	return (NULL);
}

void	*table(void *arg)
{
	t_philo	**philos;
	int		i;
	int		fin;
	int		amount;

	philos = (t_philo **)arg;
	amount = philos[0]->rules->amount;
	while (1)
	{
		i = 0;
		fin = 1;
		while (i < amount)
		{
			if (starvation(philos[i]))
				return (philos[i]);
			pthread_mutex_lock(&philos[i]->tte);
			if (philos[i]->to_eat > 0)
				fin = 0;
			pthread_mutex_unlock(&philos[i]->tte);
			i++;
		}
		if (fin)
			pthread_exit(finish(philos[0]->rules));
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_rules		*rules;
	t_philo		**philosophers;
	void		*dead;
	pthread_t	id;

	if (!(argc == 5 || argc == 6) || !is_num(argc, argv) || !par_sz(argc, argv))
		return (bad_input());
	rules = init_rules(argc, argv);
	philosophers = bear_philos(rules);
	sit_philos_down(philosophers);
	pthread_create(&id, NULL, table, philosophers);
	pthread_join(id, &dead);
	if (dead != NULL)
		print_process((t_philo *)dead, "died", RED);
	return (let_philos_free(philosophers, rules));
}
