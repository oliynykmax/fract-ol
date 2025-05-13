#ifndef FRACT_OL_H
#define FRACT_OL_H

#include "../assets/MLX42/include/MLX42/MLX42.h"
#include "../assets/libft/libft.h"
#include <math.h>
#include <stdlib.h>
#define EXIT_STR "The parameter is invalid. Available parameters are \"Julia\" and \"Mandelbrot\", you can also pass number as a second parameter, to do some changes to the rendering"
#define SIZE 640


typedef struct s_palette
{
    uint8_t         count;
    int                     cycle;
    int                     colors[16];
}       t_palette;


typedef struct s_fractal
{
    mlx_t           *mlx;
    mlx_image_t     *g_img;
    double          k;
    double          h;
    double          z_re;
    double          z_im;
    double          c_re;
    double          c_im;
    double          zoom;
    double          y;
    double          i;
    double          x;
    double          limx;
    double          limy;
    double          max_iter;
    t_palette       *palette;
    t_palette       *palettes;
    int                     palette_index;
    int                     smooth;
    int                     palette_len;
    char                    *f_type;
}                               t_fractal;

void            init(t_fractal *f);
void            ft_calc_mandelbrot(t_fractal *f);
void            ft_calc_julia(t_fractal *f);

#endif
