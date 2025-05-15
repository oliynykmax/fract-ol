/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:54:52 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/15 19:12:50 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractal.h"

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractal	*f;
	double		mouse_re;
	double		mouse_im;
	int32_t		x;
	int32_t		y;

	(void)xdelta;
	f = param;
	mlx_get_mouse_pos(f->mlx, &x, &y);
	mouse_re = (x - SIZE / 2.0) / (f->zoom * SIZE / 2.0) + f->shift_x;
	mouse_im = (y - SIZE / 2.0) / (f->zoom * SIZE / 2.0) + f->shift_y;
	if (ydelta > 0)
		f->zoom *= 1.1;
	else
		f->zoom /= 1.1;
	f->shift_x = mouse_re - (x - SIZE / 2.0) / (f->zoom * SIZE / 2.0);
	f->shift_y = mouse_im - (y - SIZE / 2.0) / (f->zoom * SIZE / 2.0);
}

void	ft_loop_hook(void *param)
{
	t_fractal	*f;

	f = param;
	if (mlx_is_key_down(f->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(f->mlx);
	if (mlx_is_key_down(f->mlx, MLX_KEY_I))
		f->max_iter = (f->max_iter * 1.1) + 1;
	if (mlx_is_key_down(f->mlx, MLX_KEY_D))
		f->max_iter /= 1.1;
	if (mlx_is_key_down(f->mlx, MLX_KEY_DOWN))
		move(MLX_KEY_DOWN, f);
	if (mlx_is_key_down(f->mlx, MLX_KEY_UP))
		move(MLX_KEY_UP, f);
	if (mlx_is_key_down(f->mlx, MLX_KEY_RIGHT))
		move(MLX_KEY_RIGHT, f);
	if (mlx_is_key_down(f->mlx, MLX_KEY_LEFT))
		move(MLX_KEY_LEFT, f);
	if (mlx_is_key_down(f->mlx, MLX_KEY_C))
		f->color_scheme = (f->color_scheme + 1) % 3;
	mlx_scroll_hook(f->mlx, &my_scrollhook, f);
	ft_draw_fract(f);
}
