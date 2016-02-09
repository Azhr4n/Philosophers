/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/13 19:04:41 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/13 19:04:42 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define WIDTH 500
# define HEIGHT 500
# define TITLE "Philo"

# define NB_PHILO 7
# define TIMEOUT 300
# define MAX_LIFE 100
# define EAT_T 4
# define REST_T 2
# define THINK_T 2

# define W_LIFEBAR 50
# define H_LIFEBAR MAX_LIFE

pthread_mutex_t			g_lock[NB_PHILO];

typedef struct			s_mlx
{
	void				*mlx_p;
	void				*win_p;
}						t_mlx;

typedef struct			s_rice_eater
{
	pthread_t			thread_id;
	struct s_rice_eater	*right;
	struct s_rice_eater	*left;
	int					right_stick;
	int					left_stick;
	int					state;
	int					stop;
	int					hp;
	int					nb;
}						t_rice_eater;

/*
**sticks_and_stones.c
*/
void					try_get_both(t_rice_eater *rice_eater);
void					no_stick(t_rice_eater *rice_eater);
void					get_right_stick(t_rice_eater *rice_eater);
void					get_left_stick(t_rice_eater *rice_eater);

/*
**set_and_co.c
*/
void					ft_pthread_init(void);
void					set_rice_eater(t_rice_eater rice_eater[7]);
void					ft_put_color(t_rice_eater rice_eater[7],
	t_mlx *mlx, int i, int j);
void					refresh_life(t_rice_eater rice_eater[7],
	t_mlx *mlx, int *cont);
void					set(t_rice_eater re[7],
	t_mlx *mlx, int *c, int *timeout);

/*
**philo.c
*/
void					ft_putstr(char *str);
void					eat(t_rice_eater *rice_eater);
void					*choice(void *arg);
int						key(int keycode, t_rice_eater rice_eater[7]);

#endif
