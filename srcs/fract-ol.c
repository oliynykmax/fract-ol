/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:32:16 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/13 16:30:43 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	hook_escape(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(param);
	}
}

void init_screen()
{
	void	*mlx;
	void	*g_img;

	mlx = mlx_init(WIDTH, HEIGHT, "Fractal", 0);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);
	// mlx_loop_hook(mlx, &hook_escape, mlx);
	mlx_key_hook(mlx, &hook_escape, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

int	main(int ac, char **av)
{
	t_fractal	*f = malloc(sizeof(t_fractal));

	is_valid_param(ac, av);
	init_screen(f);
}
