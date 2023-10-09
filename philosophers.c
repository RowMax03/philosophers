/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:47:13 by mreidenb          #+#    #+#             */
/*   Updated: 2023/10/09 13:13:22 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**bear_philos(t_rules *rules)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = malloc(rules->amount * sizeof(t_philo *));
	while (i < rules->amount)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->n = i;
		philos[i]->last_ate = rules->start_time;
		philos[i]->to_eat = rules->times_to_eat;
		philos[i]->rules = rules;
		pthread_mutex_init(&philos[i]->eating, NULL);
		pthread_mutex_init(&philos[i]->right, NULL);
		pthread_mutex_init(&philos[i]->tte, NULL);
		i++;
	}
	return (philos);
}

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->n % 4)
		p_sleep(3);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	sit_philos_down(t_philo **philos)
{
	int	i;
	int	amount;

	i = 0;
	amount = philos[0]->rules->amount;
	philos[i]->left = &philos[amount - 1]->right;
	i++;
	while (i < amount)
	{
		philos[i]->left = &philos[i - 1]->right;
		i++;
	}
	i = 0;
	while (i < amount)
	{
		pthread_create(&philos[i]->id, NULL, life, philos[i]);
		i++;
	}
}

int	let_philos_free(t_philo **philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->amount)
		pthread_detach(philos[i++]->id);
	i = 0;
	while (i < rules->amount)
	{
		pthread_mutex_destroy(&philos[i]->right);
		pthread_mutex_destroy(&philos[i]->eating);
		pthread_mutex_destroy(&philos[i]->tte);
		free(philos[i]);
		i++;
	}
	free(philos);
	free(rules);
	return (0);
}
