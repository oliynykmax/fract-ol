#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "../assets/MLX42/include/MLX42/MLX42.h"
# include "../assets/libft/libft.h"
# include <math.h>
# include <stdlib.h>
#define EXIT_STR "Usage:\n\
./fractol Mandelbrot\n\
./fractol Julia\n\
./fractol Julia <real> <imaginary>\n\
Example: ./fractol Julia -0.4 0.6"
# define SIZE 500

typedef struct s_palette
{
	uint8_t count;
	int cycle;
	int colors[16];
} t_palette;

typedef struct s_fractal
{
	void* mlx;
	void* g_img;
	char* f_type;
	int x;
	int y;
	double real;
	double imag;
	double zoom;
	double shift_x;
	double shift_y;
	int max_iter;
	int i;
	double julia_real;
	double julia_imag;
} t_fractal;

void init(t_fractal* f);
void ft_calc_mandelbrot(t_fractal* f);
void ft_calc_julia(t_fractal* f);
void ft_put_pixel(t_fractal* f);
#endif
