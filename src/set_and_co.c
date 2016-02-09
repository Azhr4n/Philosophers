/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_co.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 19:18:07 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/19 19:18:07 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <mlx.h>

#include "philo.h"

void		ft_pthread_init(void)
{
	int		i;

	i = 0;
	while (i < NB_PHILO)
	{
		if (pthread_mutex_init(&g_lock[i], 0))
			exit(-1);
		i++;
	}
}

void		set_rice_eater(t_rice_eater rice_eater[7])
{
	int		i;

	i = 0;
	while (i < NB_PHILO)
	{
		rice_eater[i].state = 1;
		rice_eater[i].stop = 0;
		rice_eater[i].hp = MAX_LIFE;
		rice_eater[i].nb = i;
		if (!i)
			rice_eater[i].right = &rice_eater[NB_PHILO - 1];
		else
			rice_eater[i].right = &rice_eater[i - 1];
		if (i == NB_PHILO - 1)
			rice_eater[i].left = &rice_eater[0];
		else
			rice_eater[i].left = &rice_eater[i + 1];
		rice_eater[i].left_stick = 1;
		rice_eater[i].right_stick = 0;
		if (pthread_create(&rice_eater[i].thread_id, 0, choice, &rice_eater[i]))
			exit(-1);
		i++;
	}
}

void		ft_put_color(t_rice_eater rice_eater[7], t_mlx *mlx, int i, int j)
{
	int		o;

	o = H_LIFEBAR;
	while (o > 0)
	{
		if (o <= rice_eater[i].hp)
		{
			if (rice_eater[i].state == 0)
				mlx_pixel_put(mlx->mlx_p, mlx->win_p, (WIDTH / NB_PHILO) * i
					+ j + 10, (HEIGHT + H_LIFEBAR) / 2 - o, 0xAA1111);
			if (rice_eater[i].state == 1)
				mlx_pixel_put(mlx->mlx_p, mlx->win_p, (WIDTH / NB_PHILO) * i
					+ j + 10, (HEIGHT + H_LIFEBAR) / 2 - o, 0x11AA11);
			if (rice_eater[i].state == 2)
				mlx_pixel_put(mlx->mlx_p, mlx->win_p, (WIDTH / NB_PHILO) * i
					+ j + 10, (HEIGHT + H_LIFEBAR) / 2 - o, 0x1111AA);
		}
		else
			mlx_pixel_put(mlx->mlx_p, mlx->win_p, (WIDTH / NB_PHILO) * i
				+ j + 10, (HEIGHT + H_LIFEBAR) / 2 - o, 0xABCDEF);
		o--;
	}
}

void		refresh_life(t_rice_eater rice_eater[7], t_mlx *mlx, int *cont)
{
	int				i;
	int				j;

	i = 0;
	while (i < NB_PHILO)
	{
		rice_eater[i].hp--;
		j = 0;
		while (j < W_LIFEBAR)
		{
			ft_put_color(rice_eater, mlx, i, j);
			j++;
		}
		if (!rice_eater[i].hp)
			*cont = 0;
		i++;
	}
}

void		set(t_rice_eater re[7], t_mlx *mlx, int *c, int *timeout)
{
	ft_putstr("Red : resting (no stick).\n");
	ft_putstr("Green : thinking (one stick).\n");
	ft_putstr("Blue : eating (two sticks).\n");
	mlx->mlx_p = mlx_init();
	mlx->win_p = mlx_new_window(mlx->mlx_p, WIDTH, HEIGHT, TITLE);
	ft_pthread_init();
	set_rice_eater(re);
	*timeout = TIMEOUT;
	*c = 1;
}
