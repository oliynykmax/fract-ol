/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:41:18 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/16 16:10:53 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractal.h"

static void	handle_close(void *param)
{
	t_fractal	*f;

	f = param;
	mlx_close_window(f->mlx);
}

void	ft_put_pixel(t_fractal *f)
{
	int		color;
	double	t;

	if (f->i >= f->max_iter)
		mlx_put_pixel(f->g_img, f->x, f->y, 0x1A1A3AFF);
	else
	{
		t = (double)f->i / f->max_iter;
		apply_color_scheme(f, t, &color);
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

void	init_screen(t_fractal *f)
{
	f->mlx = mlx_init(SIZE, SIZE, f->f_type, 0);
	if (!f->mlx)
		cleanup_and_exit(f, "MLX initialization failed");
	f->g_img = mlx_new_image(f->mlx, SIZE, SIZE);
	if (!f->g_img)
		cleanup_and_exit(f, "Failed to create new image");
	if (mlx_image_to_window(f->mlx, f->g_img, 0, 0) < 0)
		cleanup_and_exit(f, "Failed to put image to window");
	mlx_close_hook(f->mlx, &handle_close, f);
	mlx_key_hook(f->mlx, &key_hook, f);
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
	f->julia_real = -0.2;
	f->julia_imag = 0.652;
	is_valid_param(ac, av, f);
	f->mlx = NULL;
	f->f_type = &(av[1][0]);
	f->max_iter = 30;
	f->zoom = 0.5;
	f->shift_x = 0.0;
	f->shift_y = 0.0;
	f->color_scheme = 0;
	init_screen(f);
	free(f);
	return (0);
}
