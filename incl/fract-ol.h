/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:11:31 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/15 16:36:48 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "../assets/MLX42/include/MLX42/MLX42.h"
# include "../assets/libft/libft.h"
# include <math.h>
# include <stdlib.h>
# define EXIT_STR \
	"Usage:\n\
./fractol Mandelbrot\n\
./fractol Julia\n\
./fractol Julia <real> <imaginary>\n\
Example: ./fractol Julia -0.4 0.6"
# define SIZE 500

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_fractal
{
	void	*mlx;
	void	*g_img;
	char	*f_type;
	int		x;
	int		y;
	double	real;
	double	imag;
	double	zoom;
	double	shift_x;
	double	shift_y;
	int		max_iter;
	int		i;
	double	julia_real;
	double	julia_imag;
	int		color_scheme;
}			t_fractal;

void		init(t_fractal *f);
void		ft_calc_mandelbrot(t_fractal *f);
void		ft_calc_julia(t_fractal *f);
void		ft_put_pixel(t_fractal *f);
void		apply_color_scheme(t_fractal *f, double t, int *color);
void		switch_color_scheme(t_fractal *f);
void		toggle_smooth_coloring(t_fractal *f);
int			get_rgba(int r, int g, int b, int a);
void		apply_color_scheme(t_fractal *f, double t, int *color);

#endif
