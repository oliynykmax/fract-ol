/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:17:52 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/16 14:02:28 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractal.h"

static inline void	calculate_burning_ship(t_fractal *f)
{
	double	x;
	double	y;
	int		i;
	double	x_new;

	x = 0.0;
	y = 0.0;
	i = 0;
	while (i < f->max_iter)
	{
		x_new = x * x - y * y + f->real;
		y = fabs(2.0 * x * y) + f->imag;
		x = x_new;
		if (x * x + y * y > 4.0)
			break ;
		i++;
	}
	f->i = i;
}

void	is_valid_param(int ac, char **av, t_fractal *f)
{
	char	*end_ptr;

	if (ac == 2)
	{
		if (ft_memcmp(av[1], "Mandelbrot", 10) == 0 || (ft_memcmp(av[1], "Burn",
					4) == 0))
			return ;
		if (ft_memcmp(av[1], "Julia", 5) == 0)
			return ;
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

static inline void	calculate_julia(t_fractal *f)
{
	double	x;
	double	y;
	int		i;
	double	x_new;

	x = f->real;
	y = f->imag;
	i = 0;
	while (i < f->max_iter)
	{
		x_new = x * x - y * y + f->julia_real;
		y = 2.0 * x * y + f->julia_imag;
		x = x_new;
		if (x * x + y * y > 4.0)
			break ;
		i++;
	}
	f->i = i;
}

static inline void	calculate_mandelbrot(t_fractal *f)
{
	double	x;
	double	y;
	int		i;
	double	x_new;

	x = 0.0;
	y = 0.0;
	i = 0;
	while (i < f->max_iter)
	{
		x_new = x * x - y * y + f->real;
		y = 2.0 * x * y + f->imag;
		x = x_new;
		if (x * x + y * y > 4.0)
			break ;
		i++;
	}
	f->i = i;
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
			else if (ft_strncmp(f->f_type, "Burn", 4) == 0)
				calculate_burning_ship(f);
			ft_put_pixel(f);
			f->x++;
		}
		f->y++;
	}
}
