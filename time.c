/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:35:16 by mreidenb          #+#    #+#             */
/*   Updated: 2023/08/23 00:39:24 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time_ms(void)
{
	struct timeval	ts;

	gettimeofday(&ts, NULL);
	return (ts.tv_sec * 1000 + ts.tv_usec / 1000);
}

void	p_sleep(time_t ms)
{
	time_t	stop;

	stop = current_time_ms() + ms;
	while (current_time_ms() < stop)
		usleep (200);
}
