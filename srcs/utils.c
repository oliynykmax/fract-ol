/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:17:52 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/15 18:01:28 by maoliiny         ###   ########.fr       */
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
	double	x_new;
	double	x2;
	double	y2;

	x = f->real;
	y = f->imag;
	f->i = 0;
	while (f->i < f->max_iter)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 > 4.0)
			break ;
		x_new = x2 - y2 + f->julia_real;
		y = 2.0 * x * y + f->julia_imag;
		x = x_new;
		f->i++;
	}
}

void	calculate_mandelbrot(t_fractal *f)
{
	double			x_temp;
	const double	c_real = f->real;
	const double	c_imag = f->imag;
	double			x;
	double			y;

	x = 0.0;
	y = 0.0;
	f->i = 0;
	while (f->i < f->max_iter)
	{
		x_temp = x * x - y * y + c_real;
		y = 2 * x * y + c_imag;
		x = x_temp;
		if ((x * x + y * y) > 4.0)
			break ;
		f->i++;
	}
}
