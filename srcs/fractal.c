/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:41:18 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/15 18:45:55 by maoliiny         ###   ########.fr       */
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

void	ft_draw_fract(t_fractal *f)
{
	f->y = 0;
	while (f->y < SIZE)
	{
		f->x = 0;
		while (f->x < SIZE)
		{
			f->real = (2.0 * f->x - SIZE) / (f->zoom * SIZE) + f->shift_x;
			f->imag = (2.0 * f->y - SIZE) / (f->zoom * SIZE) + f->shift_y;
			if (ft_strncmp(f->f_type, "Julia", 5) == 0)
				calculate_julia(f);
			else if (ft_strncmp(f->f_type, "Mandelbrot", 10) == 0)
				calculate_mandelbrot(f);
			ft_put_pixel(f);
			f->x++;
		}
		f->y++;
	}
}

void	move(int key, t_fractal *f)
{
	double	move_speed;

	move_speed = 0.05 / f->zoom;
	if (key == MLX_KEY_LEFT)
		f->shift_x -= move_speed;
	if (key == MLX_KEY_RIGHT)
		f->shift_x += move_speed;
	if (key == MLX_KEY_UP)
		f->shift_y -= move_speed;
	if (key == MLX_KEY_DOWN)
		f->shift_y += move_speed;
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

void	init_screen(t_fractal *f)
{
	f->mlx = mlx_init(SIZE, SIZE, f->f_type, 0);
	f->g_img = mlx_new_image(f->mlx, SIZE, SIZE);
	mlx_image_to_window(f->mlx, f->g_img, 0, 0);
	mlx_loop_hook(f->mlx, &ft_loop_hook, f);
	mlx_loop(f->mlx);
	mlx_terminate(f->mlx);
}

int	main(int ac, char **av)
{
	t_fractal	*f;

	f = malloc(sizeof(t_fractal));
	if (!f)
		return (EXIT_FAILURE);
	is_valid_param(ac, av, f);
	f->f_type = &(av[1][0]);
	f->max_iter = 35;
	f->zoom = 0.5;
	f->shift_x = 0.0;
	f->shift_y = 0.0;
	f->color_scheme = 0;
	init_screen(f);
	free(f);
	return (0);
}
