/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sticks_and_stones.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 18:36:21 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/19 18:37:23 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "philo.h"

void		try_get_both(t_rice_eater *r_e)
{
	if (r_e->right->left_stick && r_e->right->hp >= r_e->hp)
	{
		if (!pthread_mutex_trylock(&g_lock[r_e->right->nb]))
		{
			r_e->right->left_stick = 0;
			r_e->right_stick = 1;
			pthread_mutex_unlock(&g_lock[r_e->right->nb]);
		}
	}
	if (r_e->left->right_stick && r_e->left->hp >= r_e->hp)
	{
		if (!pthread_mutex_trylock(&g_lock[r_e->nb]))
		{
			r_e->left->right_stick = 0;
			r_e->left_stick = 1;
			pthread_mutex_unlock(&g_lock[r_e->right->nb]);
		}
	}
}

void		no_stick(t_rice_eater *r_e)
{
	time_t	timer;

	r_e->state = 0;
	timer = time(0);
	while (time(0) - timer != REST_T)
	{
		if (r_e->stop)
			exit(0);
	}
	try_get_both(r_e);
}

void		get_right_stick(t_rice_eater *r_e)
{
	time_t	timer;

	if (r_e->right->hp == r_e->hp && r_e->left->hp == r_e->hp)
		usleep(10);
	if (!pthread_mutex_trylock(&g_lock[r_e->nb]))
	{
		r_e->state = 1;
		timer = time(0);
		while (time(0) - timer != THINK_T)
		{
			if (r_e->stop)
				exit(0);
		}
		if (r_e->right->left_stick && r_e->right->hp >= r_e->hp)
		{
			if (!pthread_mutex_trylock(&g_lock[r_e->right->nb]))
			{
				r_e->right->left_stick = 0;
				r_e->right_stick = 1;
				pthread_mutex_unlock(&g_lock[r_e->right->nb]);
			}
		}
		pthread_mutex_unlock(&g_lock[r_e->nb]);
	}
}

void		get_left_stick(t_rice_eater *r_e)
{
	time_t	timer;

	if (!pthread_mutex_trylock(&g_lock[r_e->right->nb]))
	{
		r_e->state = 1;
		timer = time(0);
		while (time(0) - timer != THINK_T)
		{
			if (r_e->stop)
				exit(0);
		}
		if (r_e->left->right_stick && r_e->left->hp >= r_e->hp)
		{
			if (!pthread_mutex_trylock(&g_lock[r_e->nb]))
			{
				r_e->left->right_stick = 0;
				r_e->left_stick = 1;
				pthread_mutex_unlock(&g_lock[r_e->nb]);
			}
		}
		pthread_mutex_unlock(&g_lock[r_e->right->nb]);
	}
}
