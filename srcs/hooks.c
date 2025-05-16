/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:54:52 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/16 16:08:46 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractal.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fractal	*f;

	f = param;
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		f->color_scheme = (f->color_scheme + 1) % 2;
		ft_draw_fract(f);
	}
}

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
	{
		f->zoom *= 1.1;
		if (f->max_iter < 300)
			f->max_iter += 1;
	}
	else
	{
		if (f->max_iter > 20)
			f->max_iter -= 1;
		f->zoom /= 1.1;
	}
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
	mlx_scroll_hook(f->mlx, &my_scrollhook, f);
	ft_draw_fract(f);
}

void	print_exit_clean(t_fractal *f)
{
	free(f);
	ft_printf("%s\n", EXIT_STR);
	exit(EXIT_FAILURE);
}

void	cleanup_and_exit(t_fractal *f, const char *error_msg)
{
	if (f)
	{
		if (f->mlx)
			mlx_terminate(f->mlx);
		free(f);
	}
	if (error_msg)
		ft_printf("Error: %s\n", error_msg);
	exit(EXIT_FAILURE);
}
