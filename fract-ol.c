/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:32:16 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/13 12:07:55 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include "libft/libft.h"
#include "MLX42/include/MLX42/MLX42.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <math.h>
// #define EXIT_STR "The parameter is invalid. Available parameters are \"Julia\" and \"Mandelbrot\", you can also pass number as a second parameter, to do some changes to the rendering"
// #define BPP sizeof(int32_t)
//static mlx_image_t	*g_img;
// void is_valid_param(int ac, char **av)
// {
//     if (ac == 2)
//     {
//         if (ft_memcmp(av[1], "Julia", 5) == 0 ||
//             ft_memcmp(av[1], "Mandelbrot", 10) == 0)
//         {
//             return;
//         }
//         ft_printf("%s\n", EXIT_STR);
//         exit(EXIT_FAILURE);
//     }
//     if (ac == 3)
//     {
//         if ((ft_memcmp(av[1], "Julia", 5) == 0 ||
//              ft_memcmp(av[1], "Mandelbrot", 10) == 0) &&
//             ft_atoi(av[2]) > 0)
//         {
//             return;
//         }
//         ft_printf("%s\n", EXIT_STR);
//         exit(EXIT_FAILURE);
//     }
//     ft_printf("%s\n", EXIT_STR);
//     exit(EXIT_FAILURE);
// }

// void hook_escape(mlx_key_data_t keydata, void* param)
// {
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
//     {
// 		mlx_close_window(param);
//     }
// }

// uint32_t get_color(int iter) {
//     if (iter == 300)
//         return 0xFF000000; // black, fully opaque
//     // Simple coloring: blue gradient
//     return 0xFF000000 | (iter * 9 % 256) << 16 | (iter * 7 % 256) << 8 | (iter * 5 % 256);
// }

// void	hook(void* param)
// {
// 	mlx_t* mlx;

//     double a = -0.7;
//     double b = 0.27015;
// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_P))
// 		mlx_delete_image(mlx, g_img);
// 	for (int x = 0; x < (int)g_img->width; x++)
// 		for(int y= 0; y < (int)g_img->height; y++)
//         {
//             double zx = 1.5 * (x - x / 2) / (0.5 * x);
//             double zy = (y - y / 2) / (0.5 * y);

//             int i;
//             for (i = 0; i < 300; i++) {
//                 double xtemp = zx * zx - zy * zy + a;
//                 zy = 2.0 * zx * zy + b;
//                 zx = xtemp;
//                 if (zx * zx + zy * zy > 4.0) break;
//             uint32_t color = get_color(i);
// 			mlx_put_pixel(g_img, x, y, color);
//         }
//     }
// }

// int get_rgba(int r, int g, int b, int a)
// 	is_valid_param(ac, av);
//     void	*mlx;
    
// 	mlx = mlx_init(1920, 1080, "Fractal", 1);
//     g_img = mlx_new_image(mlx, 1000, 1000);
//     mlx_image_to_window(mlx, g_img, 0, 0);

//     mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);
    
//     mlx_terminate(mlx);
// 	return (0);
// }    void	*mlx;
    
// 	mlx = mlx_init(1920, 1080, "Fractal", 1);
//     g_img = mlx_new_image(mlx, 1000, 1000);
//     mlx_image_to_window(mlx, g_img, 0, 0);

//     mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);
    
//     mlx_terminate(mlx);
// 	return (0);
// }




#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define INIT_WIDTH   400
#define INIT_HEIGHT  400
#define MAX_ITER     100

typedef struct s_fractal
{
  mlx_t       *mlx;
  mlx_image_t *img;
  double      cx_min, cx_max, cy_min, cy_max;
  double      a, b;                      // Julia constant
  uint32_t    palette[MAX_ITER + 1];     // precomputed colors
} t_fractal;

// build ARGB palette
static void build_palette(uint32_t *pal)
{
  for (int i = 0; i <= MAX_ITER; ++i)
  {
    if (i == MAX_ITER)
      pal[i] = 0xFF000000;
    else
    {
      uint8_t r = (i * 9) % 256;
      uint8_t g = (i * 7) % 256;
      uint8_t b = (i * 5) % 256;
      pal[i] = 0xFF000000 | (r << 16) | (g << 8) | b;
    }
  }
}

// very hot loop: write directly into pixel buffer
static void draw_julia(t_fractal *f)
{
  uint32_t w = f->img->width;
  uint32_t h = f->img->height;
  double   dx = (f->cx_max - f->cx_min) / (w - 1);
  double   dy = (f->cy_max - f->cy_min) / (h - 1);
  uint32_t *pixels = (uint32_t *)f->img->pixels;

  for (uint32_t y = 0; y < h; ++y)
  {
    double zy0 = f->cy_min + y * dy;
    uint32_t base = y * w;
    for (uint32_t x = 0; x < w; ++x)
    {
      double zx = f->cx_min + x * dx;
      double zy = zy0;
      int iter = 0;
      while (iter < MAX_ITER && zx * zx + zy * zy <= 4.0)
      {
        double xt = zx * zx - zy * zy + f->a;
        zy = 2.0 * zx * zy + f->b;
        zx = xt;
        ++iter;
      }
      pixels[base + x] = f->palette[iter];
    }
  }
}

// zoom on scroll, recenter on mouse
static void on_scroll(double _xd, double yd, void *p)
{
    (void)_xd;
  t_fractal *f = p;
  double zoom = (yd > 0) ? 0.8 : 1.25;
  int32_t mx, my;
  mlx_get_mouse_pos(f->mlx, &mx, &my);

  uint32_t w = f->img->width, h = f->img->height;
  double mouse_cx = f->cx_min + (f->cx_max - f->cx_min) * mx / (w - 1);
  double mouse_cy = f->cy_min + (f->cy_max - f->cy_min) * my / (h - 1);

  double new_w = (f->cx_max - f->cx_min) * zoom;
  double new_h = (f->cy_max - f->cy_min) * zoom;

  f->cx_min = mouse_cx - (mouse_cx - f->cx_min) * zoom;
  f->cx_max = f->cx_min + new_w;
  f->cy_min = mouse_cy - (mouse_cy - f->cy_min) * zoom;
  f->cy_max = f->cy_min + new_h;

  draw_julia(f);
}

// immediately recreate & redraw on resize
static void on_resize(int32_t w, int32_t h, void *p)
{
  t_fractal *f = p;
  if (w < 2 || h < 2) return;

  mlx_delete_image(f->mlx, f->img);
  f->img = mlx_new_image(f->mlx, w, h);
  if (!f->img)
  {
    fprintf(stderr, "new_image failed: %s\n", mlx_strerror(mlx_errno));
    mlx_close_window(f->mlx);
    return;
  }
  mlx_image_to_window(f->mlx, f->img, 0, 0);
  draw_julia(f);
}

int main(void)
{
  t_fractal f;

  // initial fractal parameters
  f.a = -0.7;  f.b = 0.27015;
  f.cx_min = -1.5; f.cx_max = 1.5;
  f.cy_min = -1.5; f.cy_max = 1.5;

  // init MLX42 (resizable)
  f.mlx = mlx_init(INIT_WIDTH, INIT_HEIGHT, "Julia (fast)", true);
  if (!f.mlx)
  {
    fprintf(stderr, "mlx_init failed: %s\n", mlx_strerror(mlx_errno));
    return EXIT_FAILURE;
  }

  // build palette once
  build_palette(f.palette);

  // create & show initial image
  f.img = mlx_new_image(f.mlx, INIT_WIDTH, INIT_HEIGHT);
  if (!f.img)
  {
    fprintf(stderr, "new_image failed: %s\n", mlx_strerror(mlx_errno));
    mlx_terminate(f.mlx);
    return EXIT_FAILURE;
  }
  draw_julia(&f);
  mlx_image_to_window(f.mlx, f.img, 0, 0);

  // hooks
  mlx_scroll_hook (f.mlx, on_scroll, &f);
  mlx_resize_hook (f.mlx, on_resize, &f);

  mlx_loop(f.mlx);
  mlx_terminate(f.mlx);
  return 0;
}


