

#include "../incl/fract-ol.h"

void	is_valid_param(int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_memcmp(av[1], "Julia", 5) == 0 || ft_memcmp(av[1], "Mandelbrot",
				10) == 0)
		{
			return ;
		}
		ft_printf("%s\n", EXIT_STR);
		exit(EXIT_FAILURE);
	}
	if (ac == 3)
	{
		if ((ft_memcmp(av[1], "Julia", 5) == 0 || ft_memcmp(av[1], "Mandelbrot",
					10) == 0) && ft_atoi(av[2]) > 0)
		{
			return ;
		}
		ft_printf("%s\n", EXIT_STR);
		exit(EXIT_FAILURE);
	}
	ft_printf("%s\n", EXIT_STR);
	exit(EXIT_FAILURE);
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractal	*f;

	(void)param;
	f = param;
	if (ydelta > 0)
		f->zoom *= 1.1;
	else if (ydelta < 0)
		f->zoom /= 1.1;
	;
	// Can also detect a mousewheel that goes along the X (e.g: MX Master 3)
	if (xdelta < 0)
		ft_printf("Sliiiide to the left!");
	else if (xdelta > 0)
		ft_printf("Sliiiide to the right!");
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_put_pixel(t_fractal *f)
{
	int	color;

	if (f->i >= f->max_iter)
		mlx_put_pixel(f->g_img, f->x, f->y, 0x000000FF);
			// Black for points in set
	else
	{
		color = get_rgba(43, 104, 50, 255);
		mlx_put_pixel(f->g_img, f->x, f->y, color);
	}
}

void	ft_draw_fract(t_fractal *f)
{
	f->y = 0;
	while (f->y < SIZE)
	{
		f->x = 0;
		while (f->x < SIZE)
		{
			ft_put_pixel(f);
			f->x++;
		}
		f->y++;
	}
}

void	ft_loop_hook(void *param)
{
	t_fractal	*f;

	f = param;
	if (mlx_is_key_down(f->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(f->mlx);
	if (mlx_is_key_down(f->mlx, MLX_KEY_I))
		f->max_iter = (f->max_iter * 1.1) + 1;
	if (mlx_is_key_down(f->mlx, MLX_KEY_D))
		f->max_iter /= 1.1;
	if (mlx_is_key_down(f->mlx, MLX_KEY_Z))
		f->zoom *= 1.1;
	if (mlx_is_key_down(f->mlx, MLX_KEY_X))
		f->zoom /= 1.1;
	// if (mlx_is_key_down(f->mlx, MLX_KEY_DOWN))
	// 	move(MLX_KEY_DOWN, f);
	// if (mlx_is_key_down(f->mlx, MLX_KEY_UP))
	// 	move(MLX_KEY_UP, f);
	// if (mlx_is_key_down(f->mlx, MLX_KEY_RIGHT))
	// 	move(MLX_KEY_RIGHT, f);
	// if (mlx_is_key_down(f->mlx, MLX_KEY_LEFT))
	// 	move(MLX_KEY_LEFT, f);
	mlx_scroll_hook(f->mlx, &my_scrollhook, f);
	ft_draw_fract(f);
}

void	init_screen(t_fractal *f)
{
	f->mlx = mlx_init(SIZE, SIZE, f->f_type, 0);
	f->g_img = mlx_new_image(f->mlx, SIZE, SIZE);
	mlx_image_to_window(f->mlx, f->g_img, 0, 0);
	// mlx_loop_hook(mlx, &hook_escape, mlx);
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
	is_valid_param(ac, av);
	f->f_type = &(av[1][0]);
	f->max_iter = 100; // Default max iterations
	f->zoom = 1;       // Default zoom level
	init_screen(f);
	free(f);
}
