/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreidenb <mreidenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:59:45 by mreidenb          #+#    #+#             */
/*   Updated: 2023/08/22 21:02:34 by mreidenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atoi_l(const char *str)
{
	int		i;
	int		minus;
	long	toi;

	i = 0;
	toi = 0;
	minus = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (ft_isdigit(str[i]) || (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			minus = -1 + (0 * i++);
		else if (str[i] == '+')
			i++;
		while (ft_isdigit(str[i]) && str[i])
		{
			toi = toi + str[i] - 48;
			if (!ft_isdigit(str[i + 1]))
				return (toi * minus);
			toi *= 10;
			i++;
		}
	}
	return (0);
}

void	print_process(t_philo *philo, char *msg, char *format)
{
	pthread_mutex_lock(&philo->rules->printing);
	printf("%s%ld \t%d\t %s%s\n", format,
		current_time_ms() - philo->rules->start_time, philo->n + 1, msg, RESET);
	pthread_mutex_unlock(&philo->rules->printing);
}

int	is_num(int argc, char *argv[])
{
	int	i;
	int	j;

	j = 1;
	while (j < argc)
	{
		i = 0;
		if (argv[j][0] == 0)
			return (0);
		while (argv[j][i])
		{
			if (ft_isdigit(argv[j][i++]) == 0)
				return (0);
		}
		j++;
	}
	return (1);
}

int	par_sz(int argc, char *argv[])
{
	int		i;
	long	par;

	i = 1;
	while (i < argc)
	{
		par = ft_atoi_l(argv[i]);
		if (par > INT_MAX)
			return (0);
		else if (par < 1)
			return (0);
		i++;
	}
	return (1);
}
