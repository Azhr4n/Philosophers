/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/13 17:31:14 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/13 17:31:16 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <mlx.h>

#include "philo.h"

void		ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

void		eat(t_rice_eater *rice_eater)
{
	time_t	timer;

	if (rice_eater->stop)
		exit(0);
	if (!pthread_mutex_trylock(&g_lock[rice_eater->nb]))
	{
		if (!pthread_mutex_trylock(&g_lock[rice_eater->right->nb]))
		{
			rice_eater->state = 2;
			timer = time(0);
			while (time(0) - timer != EAT_T)
			{
				if (rice_eater->stop)
					exit(0);
				rice_eater->hp = MAX_LIFE;
			}
		}
	}
	rice_eater->left->right_stick = 1;
	rice_eater->left_stick = 0;
	rice_eater->right->left_stick = 1;
	rice_eater->right_stick = 0;
	pthread_mutex_unlock(&g_lock[rice_eater->nb]);
	pthread_mutex_unlock(&g_lock[rice_eater->right->nb]);
}

void		*choice(void *arg)
{
	t_rice_eater	*rice_eater;

	rice_eater = (t_rice_eater *)arg;
	while (rice_eater->hp > 0)
	{
		if (rice_eater->stop)
			return (0);
		if (!rice_eater->left_stick && !rice_eater->right_stick)
			no_stick(rice_eater);
		else if (rice_eater->left_stick && !rice_eater->right_stick)
			get_right_stick(rice_eater);
		else if (!rice_eater->left_stick && rice_eater->right_stick)
			get_left_stick(rice_eater);
		if (rice_eater->left_stick && rice_eater->right_stick)
			eat(rice_eater);
	}
	return (0);
}

int			key(int keycode, t_rice_eater rice_eater[7])
{
	int		i;

	(void)keycode;
	i = 0;
	while (i < NB_PHILO)
	{
		rice_eater[i].stop = 1;
		i++;
	}
	i = 0;
	while (i < NB_PHILO)
	{
		if (pthread_join(rice_eater[i].thread_id, 0))
			return (-1);
		i++;
	}
	while (i > 0)
	{
		pthread_mutex_destroy(&g_lock[i]);
		i--;
	}
	exit(0);
}

int			main(void)
{
	t_rice_eater	rice_eater[7];
	t_mlx			mlx;
	int				timeout;
	time_t			timer;
	int				cont;

	timer = time(0);
	set(rice_eater, &mlx, &cont, &timeout);
	while (cont)
	{
		if (time(0) != timer)
		{
			timer = time(0);
			timeout--;
			refresh_life(rice_eater, &mlx, &cont);
		}
		if (!timeout)
			cont = 0;
	}
	if (!timeout)
		ft_putstr("Now, It is time... To DAAAAAAAANCE!!!\n");
	mlx_key_hook(mlx.win_p, key, rice_eater);
	mlx_loop(mlx.mlx_p);
	return (0);
}
