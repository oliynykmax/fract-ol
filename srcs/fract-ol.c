/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:41:18 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/15 13:41:36 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fract-ol.h"

void	is_valid_param(int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_memcmp(av[1], "Julia", 5) == 0 || ft_memcmp(av[1], "Mandelbrot",
				10) == 0)
		{
			return ;
		}
		ft_printf("%s\n", EXIT_STR);
		exit(EXIT_FAILURE);
	}
	if (ac == 3)
	{
		if ((ft_memcmp(av[1], "Julia", 5) == 0 || ft_memcmp(av[1], "Mandelbrot",
					10) == 0) && ft_atoi(av[2]) > 0)
		{
			return ;
		}
		ft_printf("%s\n", EXIT_STR);
		exit(EXIT_FAILURE);
	}
	ft_printf("%s\n", EXIT_STR);
	exit(EXIT_FAILURE);
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractal	*f;

	(void)xdelta;
	(void)param;
	f = param;
	if (ydelta > 0)
		f->zoom *= 1.1;
	else if (ydelta < 0)
		f->zoom /= 1.1;
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	calculate_julia(t_fractal *f)
{
	double			x_temp;
	const double	julia_real = -0.4;
	const double	julia_imag = 0.6;
	double			x;
	double			y;

	x = f->real;
	y = f->imag;
	f->i = 0;
	while (f->i < f->max_iter)
	{
		x_temp = x * x - y * y + julia_real;
		y = 2 * x * y + julia_imag;
		x = x_temp;
		if ((x * x + y * y) > 4.0)
			break ;
		f->i++;
	}
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
			ft_put_pixel(f);
			f->x++;
		}
		f->y++;
	}
}

void	ft_put_pixel(t_fractal *f)
{
	int		color;
	double	t;
	int		r;
	int		g;
	int		b;

	if (f->i >= f->max_iter)
		mlx_put_pixel(f->g_img, f->x, f->y, 0x000000FF);
	else
	{
		t = (double)f->i / f->max_iter;
		r = (int)(9 * t * 255);
		g = (int)(15 * t * t * 255);
		b = (int)(8.5 * t * t * t * 255);
		color = get_rgba(r, g, b, 255);
		mlx_put_pixel(f->g_img, f->x, f->y, color);
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
	if (mlx_is_key_down(f->mlx, MLX_KEY_Z))
		f->zoom *= 1.1;
	if (mlx_is_key_down(f->mlx, MLX_KEY_X))
		f->zoom /= 1.1;
	if (mlx_is_key_down(f->mlx, MLX_KEY_DOWN))
		move(MLX_KEY_DOWN, f);
	if (mlx_is_key_down(f->mlx, MLX_KEY_UP))
		move(MLX_KEY_UP, f);
	if (mlx_is_key_down(f->mlx, MLX_KEY_RIGHT))
		move(MLX_KEY_RIGHT, f);
	if (mlx_is_key_down(f->mlx, MLX_KEY_LEFT))
		move(MLX_KEY_LEFT, f);
	if (mlx_is_key_down(f->mlx, MLX_KEY_R))
		f->max_iter += 10;
	if (mlx_is_key_down(f->mlx, MLX_KEY_F))
	{
		f->max_iter -= 10;
		ft_printf("%i", f->max_iter);
	}
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
	is_valid_param(ac, av);
	f->f_type = &(av[1][0]);
	f->max_iter = 30;
	f->zoom = 1.0;
	f->shift_x = 0.0;
	f->shift_y = 0.0;
	init_screen(f);
	free(f);
	return (0);
}
