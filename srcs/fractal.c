/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:41:18 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/16 12:06:14 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractal.h"

static void	handle_close(void *param)
{
	t_fractal	*f;

	f = param;
	mlx_close_window(f->mlx);
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

void	init_screen(t_fractal *f)
{
	f->mlx = mlx_init(SIZE, SIZE, f->f_type, 0);
	f->g_img = mlx_new_image(f->mlx, SIZE, SIZE);
	mlx_image_to_window(f->mlx, f->g_img, 0, 0);
	mlx_close_hook(f->mlx, &handle_close, f);
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
	f->max_iter = 10;
	f->zoom = 0.5;
	f->shift_x = 0.0;
	f->shift_y = 0.0;
	f->color_scheme = 0;
	init_screen(f);
	free(f);
	return (0);
}
