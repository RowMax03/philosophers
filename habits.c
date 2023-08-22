/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:25:02 by mreidenb          #+#    #+#             */
/*   Updated: 2023/08/23 00:39:42 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// @param l_r left == 0, right != 0.
void	take_fork(t_philo *philo, int l_r)
{
	if (l_r == 0)
		pthread_mutex_lock(philo->left);
	else
		pthread_mutex_lock(&philo->right);
	print_process(philo, "has taken a fork", YELLOW);
}

void	sleeping(t_philo *philo)
{
	print_process(philo, "is sleeping", MAGENTA);
	p_sleep(philo->rules->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_process(philo, "is thinking", GREEN);
}

void	eating(t_philo *philo)
{
	take_fork(philo, philo->n % 2);
	take_fork(philo, (philo->n + 1) % 2);
	pthread_mutex_lock(&philo->eating);
	philo->last_ate = current_time_ms();
	print_process(philo, "is eating", CYAN);
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_lock(&philo->tte);
	philo->to_eat--;
	pthread_mutex_unlock(&philo->tte);
	p_sleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->right);
}
