/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:11:31 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/16 16:11:11 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include "../assets/MLX42/include/MLX42/MLX42.h"
# include "../assets/libft/libft.h"
# include <math.h>
# include <stdlib.h>
# define EXIT_STR \
	"Usage:\n\
./fractol Mandelbrot\n\
./fractol Julia\n\
./fractol Julia <real> <imaginary>\n\
./fractol Burn\n\
Example: ./fractol Julia -0.4 0.6"
# define SIZE 700

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
void		ft_put_pixel(t_fractal *f);
void		apply_color_scheme(t_fractal *f, double t, int *color);
void		switch_color_scheme(t_fractal *f);
void		apply_color_scheme(t_fractal *f, double t, int *color);
/*utils*/
void		is_valid_param(int ac, char **av, t_fractal *f);
void		print_exit_clean(t_fractal *f);
void		ft_put_pixel(t_fractal *f);
void		cleanup_and_exit(t_fractal *f, const char *error_msg);
void		ft_loop_hook(void *param);
void		my_scrollhook(double xdelta, double ydelta, void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
void		ft_draw_fract(t_fractal *f);
void		move(int key, t_fractal *f);

#endif
