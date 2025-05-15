/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:17:52 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/15 18:19:20 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractal.h"

void	print_exit_clean(t_fractal *f)
{
	free(f);
	ft_printf("%s\n", EXIT_STR);
	exit(EXIT_FAILURE);
}

void	is_valid_param(int ac, char **av, t_fractal *f)
{
	char	*end_ptr;

	if (ac == 2)
	{
		if (ft_memcmp(av[1], "Mandelbrot", 10) == 0)
			return ;
		if (ft_memcmp(av[1], "Julia", 5) == 0)
		{
			f->julia_real = -0.4;
			f->julia_imag = 0.6;
			return ;
		}
		print_exit_clean(f);
	}
	if (ac == 4 && ft_memcmp(av[1], "Julia", 5) == 0)
	{
		f->julia_real = ft_strtod(av[2], &end_ptr);
		if (*end_ptr != '\0')
			print_exit_clean(f);
		f->julia_imag = ft_strtod(av[3], &end_ptr);
		if (*end_ptr != '\0')
			print_exit_clean(f);
		return ;
	}
	print_exit_clean(f);
}

void	ft_put_pixel(t_fractal *f)
{
	int		color;
	double	t;

	if (f->i >= f->max_iter)
		mlx_put_pixel(f->g_img, f->x, f->y, 0x1F1013FF);
	else
	{
		t = (double)f->i / f->max_iter;
		apply_color_scheme(f, t, &color);
		mlx_put_pixel(f->g_img, f->x, f->y, color);
	}
}

void	calculate_julia(t_fractal *f)
{
	double	x;
	double	y;
	double	temp;

	x = (f->x - SIZE / 2.0) * f->zoom / SIZE + f->shift_x;
	y = (f->y - SIZE / 2.0) * f->zoom / SIZE + f->shift_y;
	f->i = 0;
	while (x * x + y * y < (1 << 8) && f->i < f->max_iter)
	{
		temp = x * x - y * y + f->julia_real;
		y = 2.0 * x * y + f->julia_imag;
		if (x == temp && y == y)
		{
			f->i = f->max_iter;
			break ;
		}
		x = temp;
		f->i++;
	}
}

void	calculate_mandelbrot(t_fractal *f)
{
	double	x;
	double	y;
	double	temp;
	double	c_real;
	double	c_imag;

	c_real = (f->x - SIZE / 2.0) * f->zoom / SIZE + f->shift_x;
	c_imag = (f->y - SIZE / 2.0) * f->zoom / SIZE + f->shift_y;
	x = 0.0;
	y = 0.0;
	f->i = 0;
	while (x * x + y * y < (1 << 8) && f->i < f->max_iter)
	{
		temp = x * x - y * y + c_real;
		y = 2.0 * x * y + c_imag;
		if (x == temp && y == y)
		{
			f->i = f->max_iter;
			break ;
		}
		x = temp;
		f->i++;
	}
}

