/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:32:16 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/12 20:57:18 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#define EXIT_STR "The parameter is invalid. Available parameters are \"Julia\" and \"Mandelbrot\", you can also pass number as a second parameter, to do some changes to the rendering"

void is_valid_param(int ac, char **av)
{
    if (ac == 2)
    {
        if (ft_memcmp(av[1], "Julia", 5) == 0 ||
            ft_memcmp(av[1], "Mandelbrot", 10) == 0)
        {
            return;
        }
        ft_printf("%s\n", EXIT_STR);
        exit(EXIT_FAILURE);
    }
    if (ac == 3)
    {
        if ((ft_memcmp(av[1], "Julia", 5) == 0 ||
             ft_memcmp(av[1], "Mandelbrot", 10) == 0) &&
            ft_atoi(av[2]) > 0)
        {
            return;
        }
        ft_printf("%s\n", EXIT_STR);
        exit(EXIT_FAILURE);
    }
    ft_printf("%s\n", EXIT_STR);
    exit(EXIT_FAILURE);
}

void hook_escape(mlx_key_data_t keydata, void* param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(param);
}


int main(int ac, char **av)
{
	mlx_t *window;
	
	is_valid_param(ac, av);
	window = mlx_init(1500, 1500, "Fractal", 1);
	mlx_key_hook(window, &hook_escape, window);
	mlx_loop(window);
	mlx_terminate(window);

	return (EXIT_SUCCESS);
}
